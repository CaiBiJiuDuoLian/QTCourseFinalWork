#include "borrowselect.h"
#include "ui_borrowselect.h"
#include"idatabase.h"
#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlRecord>
BorrowSelect::BorrowSelect(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BorrowSelect)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->setAlternatingRowColors(true);

    IDatabase &IDatabase=IDatabase::getInstance();
    if(IDatabase.initBorrowRecordsModel()){
        ui->tableView->setModel(IDatabase.borrowRecordsTabModel);
        ui->tableView->setSelectionModel(IDatabase.theborrowRecordsSelection);
    }
}



BorrowSelect::~BorrowSelect()
{
    delete ui;
}

void BorrowSelect::on_btSearch_clicked()
{
    QString filter =QString("readerName like '%%1%'").arg(ui->txtSearch->text());

    IDatabase::getInstance().searchRecord(filter);
}


void BorrowSelect::on_btStatistics_clicked()
{
    // 创建统计结果弹窗
    QDialog *statDialog = new QDialog(this);
    statDialog->setWindowTitle("借阅记录统计（按书名）");
    statDialog->resize(600, 400);

    // 创建表格显示统计结果
    QTableWidget *statTable = new QTableWidget(0, 2, statDialog);
    statTable->setHorizontalHeaderLabels(QStringList() << "书名" << "当前借阅数量");

    // 查询数据库统计数据
    QSqlQuery query;
    // 按书名分组统计未归还的借阅记录
    if (!query.exec("SELECT b.name, COUNT(r.record_id) AS borrow_count "
                    "FROM books b "
                    "LEFT JOIN borrow_records r ON b.book_id = r.book_id AND r.is_returned = 0 "
                    "GROUP BY b.name "
                    "ORDER BY borrow_count DESC")) {
        qDebug() << "查询失败：" << query.lastError().text(); // 输出错误信息
        return;
    }

    // 填充表格数据
    int row = 0;
    while (query.next()) {
        statTable->insertRow(row);
        statTable->setItem(row, 0, new QTableWidgetItem(query.value("name").toString()));
        statTable->setItem(row, 1, new QTableWidgetItem(QString::number(query.value("borrow_count").toInt())));
        row++;
    }

    // 设置表格布局
    QVBoxLayout *layout = new QVBoxLayout(statDialog);
    layout->addWidget(statTable);
    statDialog->setLayout(layout);

    // 显示弹窗
    statDialog->exec();
    delete statDialog; // 弹窗关闭后释放内存
}


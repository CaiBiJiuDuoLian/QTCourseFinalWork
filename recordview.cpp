

#include "recordview.h"
#include "ui_recordview.h"
#include "idatabase.h"
#include <QMessageBox> // 用于用户提示

RecordView::RecordView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RecordView)
{
    ui->setupUi(this);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    IDatabase &db = IDatabase::getInstance();
    if(db.initBorrowRecordsModel()){
        ui->tableView->setModel(db.borrowRecordsTabModel);
        ui->tableView->setSelectionModel(db.theborrowRecordsSelection);

        // 初始只显示未归还记录（is_returned=0）
        db.searchRecord("is_returned = 0");
    }
}

RecordView::~RecordView()
{
    delete ui;
}

void RecordView::on_btSearch_clicked()
{
    // 搜索时保留未归还筛选条件
    QString filter = QString("readerName like '%%1%' AND is_returned = 0")
                         .arg(ui->txtSearch->text());
    IDatabase::getInstance().searchRecord(filter);
}

void RecordView::on_btReturn_clicked()
{
    IDatabase &db = IDatabase::getInstance();
    QItemSelectionModel *selection = db.theborrowRecordsSelection;

    // 检查是否选中行
    if (!selection->hasSelection()) {
        QMessageBox::warning(this, "提示", "请先选择一条借阅记录");
        return;
    }

    QModelIndex currentIndex = selection->currentIndex();
    int row = currentIndex.row();

    // 获取is_returned字段的索引
    int returnCol = db.borrowRecordsTabModel->fieldIndex("is_returned");
    if (returnCol == -1) {
        QMessageBox::critical(this, "错误", "数据库字段is_returned不存在");
        return;
    }

    // 检查当前记录是否未归还（is_returned=0）
    QVariant isReturned = db.borrowRecordsTabModel->index(row, returnCol).data();
    if (isReturned.toInt() != 0) {
        QMessageBox::information(this, "提示", "该记录已归还，无需重复操作");
        return;
    }

    // 修改为已归还（is_returned=1）
    db.borrowRecordsTabModel->setData(db.borrowRecordsTabModel->index(row, returnCol), 1);

    // 提交到数据库
    if (db.submitRecordEdit()) {
        QMessageBox::information(this, "成功", "还书操作已完成");
        // 刷新表格，保持只显示未归还记录


        db.searchRecord("is_returned = 0");
    } else {
        QMessageBox::critical(this, "失败", "操作失败：" + db.borrowRecordsTabModel->lastError().text());
        db.revertRecordEdit(); // 回滚修改
    }
}

void RecordView::on_btBorrow_clicked()
{
    int currow = IDatabase::getInstance().addNewBorrowRecord();
    emit goBorrowRecordsEditView(currow);
}

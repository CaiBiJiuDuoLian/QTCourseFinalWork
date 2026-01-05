#include "readerfileview.h"
#include "ui_readerfileview.h"
#include"idatabase.h"
#include <QMessageBox>
ReaderFileView::ReaderFileView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReaderFileView)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->setAlternatingRowColors(true);

    IDatabase &IDatabase=IDatabase::getInstance();
    if(IDatabase.initReaderFileModel()){
        ui->tableView->setModel(IDatabase.readerFileTabModel);
        ui->tableView->setSelectionModel(IDatabase.theReaderFileSelection);
    }
}

ReaderFileView::~ReaderFileView()
{
    delete ui;
}

void ReaderFileView::on_btSearch_clicked()
{
    QString filter =QString("name like '%%1%'").arg(ui->txtSearch->text());

    IDatabase::getInstance().searchReaderFile(filter);
}


void ReaderFileView::on_btAdd_clicked()
{

    int currow=IDatabase::getInstance().addNewReaderFile();

    emit goReaderFileEditView(currow);
}


void ReaderFileView::on_btDelete_clicked()
{
    qDebug()<<"奇怪";
    IDatabase::getInstance().deleteCurrentReaderFile();
    qDebug()<<"为什么不能行";
}


void ReaderFileView::on_btEdit_clicked()
{
    QModelIndex curIndex =IDatabase::getInstance().theReaderFileSelection->currentIndex();
    if (!curIndex.isValid()) { // 检查是否选中行
        qDebug() << "未选中要修改的读者档案";
        QMessageBox::information(this, "提示", "未选中要修改的读者档案");
        return ;
    }

    emit goReaderFileEditView(curIndex.row());
}


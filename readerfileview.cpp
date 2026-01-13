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
{       //设置过滤条件
    QString filter =QString("name like '%%1%'").arg(ui->txtSearch->text());

    //调用idatabase.cpp相关函数
    IDatabase::getInstance().searchReaderFile(filter);
}


void ReaderFileView::on_btAdd_clicked()
{

    //获取模型中行号
    int currow=IDatabase::getInstance().addNewReaderFile();
//跳转到输入页面
    emit goReaderFileEditView(currow);
}


void ReaderFileView::on_btDelete_clicked()
{

    IDatabase::getInstance().deleteCurrentReaderFile();

}


void ReaderFileView::on_btEdit_clicked()
{
    //获取鼠标当前行
    QModelIndex curIndex =IDatabase::getInstance().theReaderFileSelection->currentIndex();
    if (!curIndex.isValid()) { // 检查是否选中行
        qDebug() << "未选中要修改的读者档案";
        QMessageBox::information(this, "提示", "未选中要修改的读者档案");
        return ;
    }

    emit goReaderFileEditView(curIndex.row());
}


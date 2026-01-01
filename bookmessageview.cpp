#include "bookmessageview.h"
#include "ui_bookmessageview.h"
#include"idatabase.h"
#include<QMessageBox>
BookMessageView::BookMessageView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BookMessageView)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->setAlternatingRowColors(true);

    IDatabase &IDatabase=IDatabase::getInstance();
    if(IDatabase.initBookMessageModel()){
        ui->tableView->setModel(IDatabase.bookMessageTabModel);
        ui->tableView->setSelectionModel(IDatabase.theBookMessageSelection);
    }
}

BookMessageView::~BookMessageView()
{
    delete ui;
}

void BookMessageView::on_btAdd_clicked()
{
    qDebug()<<"真你妈礼品";
    int currow=IDatabase::getInstance().addNewBookMessage();
    qDebug()<<"我就不信不过";
    emit goBookMessageEditView(currow);
}


void BookMessageView::on_btSearch_clicked()
{
    QString filter =QString("name like '%%1%'").arg(ui->txtSearch->text());

    IDatabase::getInstance().searchBookMessage(filter);
}


void BookMessageView::on_btDelete_clicked()
{
    qDebug()<<"奇怪";
    IDatabase::getInstance().deleteCurrentBookMessage();
    qDebug()<<"为什么不能行";
}


void BookMessageView::on_btEdit_clicked()
{

    QModelIndex curIndex =IDatabase::getInstance().theBookMessageSelection->currentIndex();
    if (!curIndex.isValid()) { // 检查是否选中行
        qDebug() << "未选中要修改的读者档案";
        QMessageBox::information(this, "提示", "未选中要修改的图书信息");
        return ;
    }
    // QModelIndex curIndex=
    //     IDatabase::getInstance().theBookMessageSelection->currentIndex();
    emit goBookMessageEditView(curIndex.row());
}


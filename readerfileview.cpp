#include "readerfileview.h"
#include "ui_readerfileview.h"
#include"idatabase.h"
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
    qDebug()<<"真你妈礼品";
    int currow=IDatabase::getInstance().addNewReaderFile();
    qDebug()<<"我就不信不过";
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
    QModelIndex curIndex=
        IDatabase::getInstance().theReaderFileSelection->currentIndex();
    emit goReaderFileEditView(curIndex.row());
}


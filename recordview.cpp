#include "recordview.h"
#include "ui_recordview.h"
#include"idatabase.h"
RecordView::RecordView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RecordView)
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

RecordView::~RecordView()
{
    delete ui;
}

void RecordView::on_btSearch_clicked()
{
    QString filter =QString("readerName like '%%1%'").arg(ui->txtSearch->text());

    IDatabase::getInstance().searchRecord(filter);
}


void RecordView::on_btReturn_clicked()
{

}


void RecordView::on_btBorrow_clicked()
{
    qDebug()<<"真你妈礼品";
    int currow=IDatabase::getInstance().addNewBorrowRecord();
    qDebug()<<"我就不信不过";
    emit goBorrowRecordsEditView(currow);
}


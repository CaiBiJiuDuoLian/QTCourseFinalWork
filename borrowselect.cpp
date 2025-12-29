#include "borrowselect.h"
#include "ui_borrowselect.h"
#include"idatabase.h"
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

    IDatabase::getInstance().searchBorrowRecords(filter);
}


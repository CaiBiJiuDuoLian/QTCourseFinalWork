#include "borrowselect.h"
#include "ui_borrowselect.h"

BorrowSelect::BorrowSelect(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BorrowSelect)
{
    ui->setupUi(this);
}

BorrowSelect::~BorrowSelect()
{
    delete ui;
}

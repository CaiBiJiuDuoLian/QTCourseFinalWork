#include "bookmessageview.h"
#include "ui_bookmessageview.h"

BookMessageView::BookMessageView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BookMessageView)
{
    ui->setupUi(this);
}

BookMessageView::~BookMessageView()
{
    delete ui;
}

#include "loginview.h"
#include "ui_loginview.h"

loginView::loginView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::loginView)
{
    ui->setupUi(this);
}

loginView::~loginView()
{
    delete ui;
}

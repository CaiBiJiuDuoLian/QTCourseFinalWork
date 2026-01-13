#include "loginview.h"
#include "ui_loginview.h"
#include<QDebug>
#include"idatabase.h"
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

void loginView::on_btSignin_clicked()
{


    QString status= IDatabase::getInstance().userLogin(ui->inputUsername->text(),ui->inputPassword->text());
    if(status=="loginOK")
        emit LoginSuccess();

}


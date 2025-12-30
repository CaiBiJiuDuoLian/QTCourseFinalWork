#include "welcomeview.h"
#include "ui_welcomeview.h"
#include<QDebug>
WelcomeView::WelcomeView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WelcomeView)
{
    ui->setupUi(this);
}

WelcomeView::~WelcomeView()
{
    delete ui;
}


void WelcomeView::on_btMessage_clicked()
{
    qDebug()<<"weish1";
    emit goBookMessageView();
    qDebug()<<"weish1";
}


void WelcomeView::on_btFile_clicked()
{
    qDebug()<<"zhe为啥";
    emit  goReaderFileView();
}


void WelcomeView::on_btRecord_clicked()
{
    emit  goRecordView();
}


void WelcomeView::on_btSelect_clicked()
{
    emit goBorrowSelectView();
}


#include "masterview.h"
#include "ui_masterview.h"
#include<QDebug>
MasterView::MasterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterView)
{
    ui->setupUi(this);
    goLoginView();

}

MasterView::~MasterView()
{
    delete ui;
}

void MasterView::pushWidgetToStackView(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);
    int count=ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count -1);
    ui->labelTitle->setText(widget->windowTitle());
}

void MasterView::on_btBack_clicked()
{
    goPreviousView();
}


void MasterView::on_btLogout_clicked()
{
    goPreviousView();
}

void MasterView::on_stackedWidget_currentChanged(int arg1)
{

    qDebug()<< "why";
    int count =ui->stackedWidget->count();
    if(count>1)
        ui->btBack->setEnabled(true);
    else
        ui->btBack->setEnabled(false);
    QString title=ui->stackedWidget->currentWidget()->windowTitle();
    if(title=="欢迎"){
        ui->btLogout->setEnabled(true);
        ui->btBack->setEnabled(false);
    }
    else
        ui->btLogout->setEnabled(false);
    if(title=="登录"){
        ui->btBack->setEnabled(false);
    }
}

void MasterView::goLoginView()
{

    login_view=new loginView(this);
    pushWidgetToStackView(login_view);
    //成功登录就跳转到欢迎页面。
    connect(login_view,SIGNAL(LoginSuccess()),this,SLOT(goWelcomeView()));
}

void MasterView::goWelcomeView()
{
    welcome_view=new WelcomeView(this);
    pushWidgetToStackView(welcome_view);
    connect(welcome_view,SIGNAL(goBookMessageView()),this,SLOT(goBookMessageView()));
    connect(welcome_view,SIGNAL(goBorrowSelectView()),this,SLOT(goBorrowSelectView()));
    connect(welcome_view,SIGNAL(goRecordView()),this,SLOT(goRecordView()));
    connect(welcome_view,SIGNAL(goReaderFileView()),this,SLOT(goReaderFileView()));
}

void MasterView::goBookMessageEditView(int rowNo)
{

}

void MasterView::goBookMessageView()
{
    book_message_view=new BookMessageView(this);
    pushWidgetToStackView(book_message_view);
}


void MasterView::goBorrowBookEditView(int rowNo)
{

}

void MasterView::goBorrowSelectView()
{
    borrow_select=new BorrowSelect(this);
    pushWidgetToStackView(borrow_select);
}

void MasterView::goReaderFileEditView(int rowNo)
{

}

void MasterView::goReaderFileView()
{
    reader_file_view=new ReaderFileView(this);
    pushWidgetToStackView(reader_file_view);
}

void MasterView::goRecordView()
{
    record_view=new RecordView(this);
    pushWidgetToStackView(record_view);
}

void MasterView::goPreviousView()
{
    qDebug()<< "test";
    int count=ui->stackedWidget->count();
    if(count>1){
        ui->stackedWidget->setCurrentIndex(count-2);
        //on_stackedWidget_currentChanged(1);
        ui->labelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());
        QWidget *widget= ui->stackedWidget->widget(count-1);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }
}


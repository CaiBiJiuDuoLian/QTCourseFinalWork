#include "masterview.h"
#include "ui_masterview.h"
#include<QDebug>
#include"idatabase.h"
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

    book_message_edit_view=new bookMessageEditView(this,rowNo);

    pushWidgetToStackView(book_message_edit_view);

    connect(book_message_edit_view,SIGNAL(goPreviousView()),this,SLOT(goPreviousView()));
}

void MasterView::goBookMessageView()
{
    book_message_view=new BookMessageView(this);
    pushWidgetToStackView(book_message_view);
    connect(book_message_view,SIGNAL(goBookMessageEditView(int)),this,SLOT(goBookMessageEditView(int)));
}


void MasterView::goBorrowBookEditView(int rowNo)
{
    borrow_book_edit_view=new borrowBookEditView(this,rowNo);

    pushWidgetToStackView( borrow_book_edit_view);



    connect( borrow_book_edit_view,SIGNAL(goPreviousView()),this,SLOT(goPreviousView()));
}

void MasterView::goBorrowSelectView()
{
    borrow_select=new BorrowSelect(this);
    pushWidgetToStackView(borrow_select);
}

void MasterView::goReaderFileEditView(int rowNo)
{
    reader_file_edit_view=new readerFileEditView(this,rowNo);

    pushWidgetToStackView(reader_file_edit_view);

    connect(reader_file_edit_view,SIGNAL(goPreviousView()),this,SLOT(goPreviousView()));
}

void MasterView::goReaderFileView()
{
    qDebug()<<"这里为什么没执行??";
    reader_file_view=new ReaderFileView(this);
    qDebug()<<"这里为什么没执行";
    pushWidgetToStackView(reader_file_view);
        qDebug()<<"这里执行了吗";
    connect(reader_file_view,SIGNAL(goReaderFileEditView(int)),this,SLOT(goReaderFileEditView(int)));
}

void MasterView::goRecordView()
{
    record_view=new RecordView(this);
    pushWidgetToStackView(record_view);

    //IDatabase::getInstance().searchRecord("is_returned=0 AND (readerName!=' ' or readerName!=' ') ");
    connect( record_view,SIGNAL(goBorrowRecordsEditView(int)),this,SLOT(goBorrowBookEditView(int)));
}

void MasterView::goPreviousView()
{
    // 获取数据库单例实例
    IDatabase& db = IDatabase::getInstance();
    // 判断借阅RecordsTabModel 是否已经初始化（不为空）
    if (db.borrowRecordsTabModel != nullptr) {
        // 模型已初始化，执行查询
        db.searchRecord("is_returned=0 AND (readerName!=' ' or bookName!=' ') ");
    } else {
        qDebug() << "借阅RecordsTabModel 未初始化，不执行查询";
    }


    qDebug()<<"为什么突然不能运行了";
  // IDatabase::getInstance().searchRecord("is_returned=0 AND (readerName!=' ' or bookName!=' ') ");
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


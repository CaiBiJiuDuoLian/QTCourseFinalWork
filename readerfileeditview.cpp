#include "readerfileeditview.h"
#include "ui_readerfileeditview.h"
#include"idatabase.h"
#include<QMessageBox>
readerFileEditView::readerFileEditView(QWidget *parent,int index)
    : QWidget(parent)
    , ui(new Ui::readerFileEditView)
{
    ui->setupUi(this);

    dataMapper=new QDataWidgetMapper(this); // 关键：给mapper设置父对象，避免内存泄漏

    QSqlTableModel *tabModel=IDatabase::getInstance().readerFileTabModel;

    dataMapper->setModel(tabModel);

    dataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);



    dataMapper->addMapping(ui->ReaderNameInput,tabModel->fieldIndex("name"));
    dataMapper->addMapping(ui->readerPhoneInput,tabModel->fieldIndex("phone"));
    dataMapper->setCurrentIndex(index);
    qDebug()<<"映射完成，当前行："<<index;
}

readerFileEditView::~readerFileEditView()
{
    delete ui;
}

void readerFileEditView::on_btSave_clicked()
{


    // 1. 检查必填字段是否为空
    QString name = ui->ReaderNameInput->text().trimmed();
    QString phone = ui->readerPhoneInput->text().trimmed();


    if (name.isEmpty() || phone.isEmpty() ) {
        QMessageBox::warning(this, "提示", "部分信息未填满，请请完善所有必填字段后再保存！");
        IDatabase::getInstance().searchReaderFile("name!=' '");
        return; // 直接返回，不执行后续提交操作
    }


    // 1. 手动提交mapper的控件值到模型
    dataMapper->submit();
    qDebug()<<"mapper提交完成";

    // 2. 提交模型到数据库
    bool ok = IDatabase::getInstance().submitReaderFileEdit();
    if(ok){
        qDebug()<<"数据写入数据库成功";
        emit goPreviousView();
    }else{
        qDebug()<<"写入失败："<<IDatabase::getInstance().readerFileTabModel->lastError().text();
        // 回滚
        IDatabase::getInstance().revertReaderFileEdit();
    }
}


void readerFileEditView::on_btCancel_clicked()
{
    IDatabase::getInstance().revertReaderFileEdit();
    emit goPreviousView();
}


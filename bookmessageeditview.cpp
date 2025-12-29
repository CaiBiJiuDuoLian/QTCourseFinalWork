#include "bookmessageeditview.h"
#include "ui_bookmessageeditview.h"
#include<QSqlTableModel>
#include "idatabase.h"
#include"masterview.h"
#include"bookmessageview.h"
bookMessageEditView::bookMessageEditView(QWidget *parent,int index)
    : QWidget(parent)
    , ui(new Ui::bookMessageEditView)
{
    ui->setupUi(this);

    dataMapper=new QDataWidgetMapper(this); // 关键：给mapper设置父对象，避免内存泄漏
    qDebug()<<"草泥马2";
    QSqlTableModel *tabModel=IDatabase::getInstance().bookMessageTabModel;
    qDebug()<<"草泥马3";
    dataMapper->setModel(tabModel);
    qDebug()<<"草泥马4";
    // 临时改为手动提交，避免AutoSubmit失效
    dataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    qDebug()<<"草泥马5";

    // 核对字段名！必须和数据库表完全一致（比如MOBILPHONE是否是MOBILEPHONE）
    dataMapper->addMapping(ui->bookNameInput,tabModel->fieldIndex("name"));
    dataMapper->addMapping(ui->authorNameInput,tabModel->fieldIndex("author")); // 核心必填字段
    dataMapper->addMapping(ui->stockNumberInput,tabModel->fieldIndex("stock"));
    dataMapper->setCurrentIndex(index);
    qDebug()<<"映射完成，当前行："<<index;

}

bookMessageEditView::~bookMessageEditView()
{
    delete ui;
}

void bookMessageEditView::on_btSave_clicked()
{
    // 1. 手动提交mapper的控件值到模型（关键！）
    dataMapper->submit();
    qDebug()<<"mapper提交完成";

    // 2. 提交模型到数据库
    bool ok = IDatabase::getInstance().submitBookMessageEdit();
    if(ok){
        qDebug()<<"数据写入数据库成功";
        emit goPreviousView();
    }else{
        qDebug()<<"写入失败："<<IDatabase::getInstance().bookMessageTabModel->lastError().text();
        // 回滚
        IDatabase::getInstance().revertBookMessageEdit();
    }
}


void bookMessageEditView::on_btCancel_clicked()
{
    IDatabase::getInstance().revertBookMessageEdit();
    emit goPreviousView();
}


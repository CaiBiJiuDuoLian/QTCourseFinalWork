#include "bookmessageeditview.h"
#include "ui_bookmessageeditview.h"
#include<QSqlTableModel>
#include "idatabase.h"
#include"masterview.h"
#include"bookmessageview.h"
#include <QMessageBox>
bookMessageEditView::bookMessageEditView(QWidget *parent,int index)
    : QWidget(parent)
    , ui(new Ui::bookMessageEditView)
{
    ui->setupUi(this);

    dataMapper=new QDataWidgetMapper(this); // 关键：给mapper设置父对象，避免内存泄漏

    QSqlTableModel *tabModel=IDatabase::getInstance().bookMessageTabModel;    //创建模型

    dataMapper->setModel(tabModel);     //设置Map模型


    dataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);



    dataMapper->addMapping(ui->bookNameInput,tabModel->fieldIndex("name"));        //在模型中插入数据表字段
    dataMapper->addMapping(ui->authorNameInput,tabModel->fieldIndex("author"));
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
    // 1. 检查必填字段是否为空
    QString bookName = ui->bookNameInput->text().trimmed();
    QString author = ui->authorNameInput->text().trimmed();
    QString stock = ui->stockNumberInput->text().trimmed();

    // 检查核心必填字段（根据实际业务逻辑调整需要检查的字段）
    if (bookName.isEmpty() || author.isEmpty() || stock.isEmpty()) {
        QMessageBox::warning(this, "提示", "部分信息未填满，请请完善所有必填字段后再保存！");
        IDatabase::getInstance().searchBookMessage("name!=' '");
        return; // 直接返回，不执行后续提交操作
    }


    // 1. 手动提交mapper的控件值到模型
    dataMapper->submit();

    //先将数据提交到模型中，然后再统一提交到模型中
    // 2. 提交模型到数据库
    bool ok = IDatabase::getInstance().submitBookMessageEdit();
    if(ok){
        qDebug()<<"数据写入数据库成功";
        //保存成功就返回上一页面
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


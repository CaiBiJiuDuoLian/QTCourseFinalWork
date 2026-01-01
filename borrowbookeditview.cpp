#include "borrowbookeditview.h"
#include "ui_borrowbookeditview.h"
#include"idatabase.h"
#include<QMessageBox>
borrowBookEditView::borrowBookEditView(QWidget *parent,int index)
    : QWidget(parent)
    , ui(new Ui::borrowBookEditView)
{
    ui->setupUi(this);

    //12.31.00测试豆包代码
    // 初始化延迟查询定时器（500ms延迟，避免输入时频繁查询数据库）
    readerQueryTimer = new QTimer(this);
    readerQueryTimer->setSingleShot(true); // 单次触发
    readerQueryTimer->setInterval(500);
    bookQueryTimer = new QTimer(this);
    bookQueryTimer->setSingleShot(true);
    bookQueryTimer->setInterval(500);

    // 绑定定时器信号到查询槽函数
    connect(readerQueryTimer, &QTimer::timeout, [this]() {
        queryReaderId(ui->readerNameInput->text().trimmed());
    });
    connect(bookQueryTimer, &QTimer::timeout, [this]() {
        queryBookId(ui->bookNameInput->text().trimmed());
    });

    // 绑定输入框文本变化信号到定时器（输入时触发延迟查询）
    connect(ui->readerNameInput, &QLineEdit::textChanged, [this](const QString &text) {
        readerQueryTimer->stop(); // 先停止之前的定时器，避免重复查询
        if (!text.isEmpty()) readerQueryTimer->start(); // 文本非空时启动定时器
    });
    connect(ui->bookNameInput, &QLineEdit::textChanged, [this](const QString &text) {
        bookQueryTimer->stop();
        if (!text.isEmpty()) bookQueryTimer->start();
    });







    dataMapper=new QDataWidgetMapper(this); // 关键：给mapper设置父对象，避免内存泄漏
    qDebug()<<"草泥马2";
    QSqlTableModel *tabModel=IDatabase::getInstance().borrowRecordsTabModel;
    qDebug()<<"草泥马3";
    dataMapper->setModel(tabModel);
    qDebug()<<"草泥马4";
    // 临时改为手动提交，避免AutoSubmit失效
    dataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    qDebug()<<"草泥马5";


    // 核对字段名！必须和数据库表完全一致（比如MOBILPHONE是否是MOBILEPHONE）
    dataMapper->addMapping(ui->bookIdInput,tabModel->fieldIndex("book_id"));
    dataMapper->addMapping(ui->readerIdInput,tabModel->fieldIndex("reader_id"));
    dataMapper->addMapping(ui->bookNameInput,tabModel->fieldIndex("bookName"));
    dataMapper->addMapping(ui->readerNameInput,tabModel->fieldIndex("readerName")); // 核心必填字段
    dataMapper->addMapping(ui->dueTimeInput,tabModel->fieldIndex("due_time"));
    dataMapper->addMapping(ui->borrowTimeInput,tabModel->fieldIndex("borrow_time")); // 核心必填字段



    //12.31.00 测试豆包代码
    // 新增借阅记录时，默认设置is_returned为0（未归还）
    if (index == tabModel->rowCount()) { // 新增行（index是最后一行）
        QModelIndex isReturnedIndex = tabModel->index(index, tabModel->fieldIndex("is_returned"));
        tabModel->setData(isReturnedIndex, 0); // 0表示未归还
    }





    dataMapper->setCurrentIndex(index);
    qDebug()<<"映射完成，当前行："<<index;
}

borrowBookEditView::~borrowBookEditView()
{
    delete ui;
}



//12.31.00测试豆包代码
// 读者名输入变化时触发（启动延迟查询）
void borrowBookEditView::on_readerNameInput_textChanged(const QString &text)
{
    readerQueryTimer->stop();
    if (!text.isEmpty()) readerQueryTimer->start();
}

// 书名输入变化时触发（启动延迟查询）
void borrowBookEditView::on_bookNameInput_textChanged(const QString &text)
{
    bookQueryTimer->stop();
    if (!text.isEmpty()) bookQueryTimer->start();
}

// 查询读者ID（根据读者名查询readers表）
void borrowBookEditView::queryReaderId(const QString &readerName)
{
    IDatabase &db = IDatabase::getInstance();
    // 1. 检查readers模型是否初始化
    if (db.readerFileTabModel == nullptr) {
        if (!db.initReaderFileModel()) {
            qDebug() << "初始化读者模型失败，无法查询reader_id";
            return;
        }
    }

    // 2. 构建查询条件（模糊匹配读者名，若读者名唯一可改用=）
    QString filter = QString("name like '%%1%'").arg(readerName);
    db.searchReaderFile(filter); // 应用过滤条件

    // 3. 获取查询结果（假设读者名唯一，取第一行的reader_id）
    QSqlTableModel *readerModel = db.readerFileTabModel;
    if (readerModel->rowCount() > 0) {
        QString readerId = readerModel->record(0).value("reader_id").toString();
        ui->readerIdInput->setText(readerId); // 填充到隐藏控件
        qDebug() << "匹配到reader_id：" << readerId;
    } else {
        ui->readerIdInput->clear();
        qDebug() << "未找到读者：" << readerName;
        // 可选：弹出提示框告知用户未找到该读者
        // QMessageBox::warning(this, "提示", "未找到该读者，请检查输入！");
    }
}

// 查询图书ID（根据书名查询books表）
void borrowBookEditView::queryBookId(const QString &bookName)
{
    IDatabase &db = IDatabase::getInstance();
    // 1. 检查books模型是否初始化
    if (db.bookMessageTabModel == nullptr) {
        if (!db.initBookMessageModel()) {
            qDebug() << "初始化图书模型失败，无法查询book_id";
            return;
        }
    }

    // 2. 构建查询条件（模糊匹配书名，若书名唯一可改用=）
    QString filter = QString("name like '%%1%'").arg(bookName);
    db.searchBookMessage(filter); // 应用过滤条件

    // 3. 获取查询结果（假设书名唯一，取第一行的book_id）
    QSqlTableModel *bookModel = db.bookMessageTabModel;
    if (bookModel->rowCount() > 0) {
        QString bookId = bookModel->record(0).value("book_id").toString();
        ui->bookIdInput->setText(bookId); // 填充到隐藏控件
        qDebug() << "匹配到book_id：" << bookId;
    } else {
        ui->bookIdInput->clear();
        qDebug() << "未找到图书：" << bookName;
        // 可选：弹出提示框告知用户未找到该图书
        // QMessageBox::warning(this, "提示", "未找到该图书，请检查输入！");
    }
}


























void borrowBookEditView::on_btBorrow_clicked()
{


    //12.31测试豆包代码
    // 1. 验证必要字段（reader_id和book_id必须匹配成功，否则不允许提交）
    QString readerId = ui->readerIdInput->text().trimmed();
    QString bookId = ui->bookIdInput->text().trimmed();
    QString borrowTime = ui->borrowTimeInput->text().trimmed();
    QString dueTime = ui->dueTimeInput->text().trimmed();

    if (readerId.isEmpty() || bookId.isEmpty()) {
        qDebug() << "提交失败：读者ID或图书ID未匹配到";
         QMessageBox::critical(this, "错误", "请输入正确的读者名和书名，确保系统能匹配到ID！");
        IDatabase::getInstance().searchRecord("readerName<>' ' or readerName<>' ' ");
        return;
    }
    if (borrowTime.isEmpty() || dueTime.isEmpty()) {
        qDebug() << "提交失败：借阅时间或到期时间未填写";
        // QMessageBox::critical(this, "错误", "请填写完整的借阅时间和到期时间！");
        return;
    }














    // 1. 手动提交mapper的控件值到模型（关键！）
    dataMapper->submit();
    qDebug()<<"mapper提交完成";

    // 2. 提交模型到数据库
    bool ok = IDatabase::getInstance().submitRecordEdit();
    if(ok){
        qDebug()<<"数据写入数据库成功";
        emit goPreviousView();
    }else{
        qDebug()<<"写入失败："<<IDatabase::getInstance().borrowRecordsTabModel->lastError().text();
        // 回滚
        IDatabase::getInstance().revertRecordEdit();
    }
}


void borrowBookEditView::on_btCancel_clicked()
{
    IDatabase::getInstance().revertRecordEdit();
    IDatabase::getInstance().searchRecord("is_returned=0 AND (readerName<>' ' or bookName<>' ') ");
    emit goPreviousView();
}


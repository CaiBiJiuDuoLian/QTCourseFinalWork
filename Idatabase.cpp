#include "idatabase.h"
#include<QDebug>
#include<QUuid>
#include<QMessageBox>
void IDatabase::initDatabase()
{
    // 避免重复添加连接
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        database = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        database = QSqlDatabase::addDatabase("QSQLITE");
    }

    QString aFile = "C:\\Users\\cd050\\Desktop\\QTHomeWork\\CourseHomework\\book_system.db";
    database.setDatabaseName(aFile);

    if (!database.open()) {
        qDebug() << "打开数据库失败：" << database.lastError().text();
        // 可抛出异常或返回错误码
    } else {
        qDebug() << "数据库打开成功";
    }
}


bool IDatabase::initBookMessageModel()
{

    if (!database.isOpen()) { // 先检查数据库是否打开
        qDebug() << "数据库未打开，初始化模型失败";
        return false;
    }
    bookMessageTabModel=new QSqlTableModel(this,database);

    bookMessageTabModel->setTable("books");

    bookMessageTabModel->setEditStrategy(QSqlTableModel ::OnManualSubmit);
    bookMessageTabModel->setSort(bookMessageTabModel->fieldIndex("name"),Qt::AscendingOrder);

    if(!(bookMessageTabModel->select())) {
        qDebug() << "查询books表失败：" << bookMessageTabModel->lastError().text();
        return false;
    }
    theBookMessageSelection=new QItemSelectionModel(bookMessageTabModel);

    return true;
}

bool IDatabase::initBorrowRecordsModel()
{
    qDebug() << "===== 初始化患者模型 =====";
    if (!database.isOpen()) { // 先检查数据库是否打开
        qDebug() << "数据库未打开，初始化模型失败";
        return false;
    }

    borrowRecordsTabModel=new QSqlTableModel(this,database);
    qDebug() << "borrowRecordsTabModel 创建：" << borrowRecordsTabModel; // 打印指针地址，若为0则崩溃
    borrowRecordsTabModel->setTable("borrow_records");
    qDebug() << "设置表为borrow_records：" << borrowRecordsTabModel->lastError().text();
    borrowRecordsTabModel->setEditStrategy(QSqlTableModel ::OnManualSubmit);
    borrowRecordsTabModel->setSort(borrowRecordsTabModel->fieldIndex("book_id"),Qt::AscendingOrder);
    qDebug() << "排序字段：" << borrowRecordsTabModel->fieldIndex("book_id"); // 若为-1，说明字段名错误
    if(!(borrowRecordsTabModel->select())) {
        qDebug() << "查询borrow_records表失败：" << borrowRecordsTabModel->lastError().text();
        return false;
    }
    theborrowRecordsSelection=new QItemSelectionModel(borrowRecordsTabModel);
    qDebug() << "theborrowRecordsSelection 创建：" << theborrowRecordsSelection;
    return true;
}


//读者档案模型
bool IDatabase::initReaderFileModel()
{
    qDebug() << "===== 初始化患者模型 =====";
    if (!database.isOpen()) { // 先检查数据库是否打开
        qDebug() << "数据库未打开，初始化模型失败";
        return false;
    }
    readerFileTabModel=new QSqlTableModel(this,database);

    readerFileTabModel->setTable("readers");

    readerFileTabModel->setEditStrategy(QSqlTableModel ::OnManualSubmit);
   readerFileTabModel->setSort(readerFileTabModel->fieldIndex("reader_id"),Qt::AscendingOrder);

    if(!(readerFileTabModel->select())) {
        qDebug() << "查询books表失败：" << readerFileTabModel->lastError().text();
        return false;
    }
    theReaderFileSelection=new QItemSelectionModel(readerFileTabModel);

    return true;
}



int IDatabase::addNewBookMessage()
{
    //插入模型
    bookMessageTabModel->insertRow(bookMessageTabModel->rowCount(),
                               QModelIndex());
    QModelIndex curIndex=bookMessageTabModel->index(bookMessageTabModel->rowCount()-1,
                                                  1);

    //获取模型中该数据行号
    int curRecNo=curIndex.row();
    //获取数据行
    QSqlRecord curRec=bookMessageTabModel->record(curRecNo);
    //将模型数据行中未插入的字段自己补充，比如id
    curRec.setValue("book_id",QUuid::createUuid().toString(QUuid::WithoutBraces));
    bookMessageTabModel->setRecord(curRecNo,curRec);
    return curIndex.row();

}

int IDatabase::addNewReaderFile()
{
    readerFileTabModel->insertRow(readerFileTabModel->rowCount(),
                                   QModelIndex());
    QModelIndex curIndex=readerFileTabModel->index(readerFileTabModel->rowCount()-1,
                                                      1);

    int curRecNo=curIndex.row();
    QSqlRecord curRec=readerFileTabModel->record(curRecNo);
    // curRec.setValue("CREATEDTIMESAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("book_id",QUuid::createUuid().toString(QUuid::WithoutBraces));
    readerFileTabModel->setRecord(curRecNo,curRec);
    return curIndex.row();

}

int IDatabase::addNewBorrowRecord()
{
    borrowRecordsTabModel->insertRow(borrowRecordsTabModel->rowCount(),
                                  QModelIndex());
    QModelIndex curIndex=borrowRecordsTabModel->index(borrowRecordsTabModel->rowCount()-1,
                                                     1);

    int curRecNo=curIndex.row();
    QSqlRecord curRec=borrowRecordsTabModel->record(curRecNo);
    //此处可以设置值，而不是输入
    // curRec.setValue("CREATEDTIMESAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    //curRec.setValue("book_id",QUuid::createUuid().toString(QUuid::WithoutBraces));
    borrowRecordsTabModel->setRecord(curRecNo,curRec);
    return curIndex.row();

}



bool IDatabase::searchBookMessage(QString filter)
{
    //过滤模型数据
    bookMessageTabModel->setFilter(filter);
    bool ok = bookMessageTabModel->select(); // 应用过滤并重新查询，显示到页面上
    if (!ok) {
        qDebug() << "查询失败：" << bookMessageTabModel->lastError().text();
    }
    return ok;
}

bool IDatabase::searchRecord(QString filter)
{
    borrowRecordsTabModel->setFilter(filter);
    bool ok = borrowRecordsTabModel->select(); // 应用过滤并重新查询
    if (!ok) {
        qDebug() << "查询失败：" << borrowRecordsTabModel->lastError().text();
    }
    return ok;
}

bool IDatabase::searchReaderFile(QString filter)
{
    readerFileTabModel->setFilter(filter);
    bool ok = readerFileTabModel->select(); // 应用过滤并重新查询
    if (!ok) {
        qDebug() << "查询失败：" << readerFileTabModel->lastError().text();
    }
    return ok;
}



bool IDatabase::deleteCurrentBookMessage()
{
    //获取鼠标选中行
    QModelIndex curIndex = theBookMessageSelection->currentIndex();
    if (!curIndex.isValid()) { // 检查是否选中行
        qDebug() << "未选中要删除的患者";
        QMessageBox::information(nullptr, "提示", "未选中要删除的图书信息");
        return false;
    }

    if (!bookMessageTabModel->removeRow(curIndex.row())) { // 移除内存中的行
        qDebug() << "移除行失败：" << bookMessageTabModel->lastError().text();
        return false;
    }

    if (!bookMessageTabModel->submitAll()) { // 提交删除到数据库
        qDebug() << "删除提交失败：" << bookMessageTabModel->lastError().text();
        bookMessageTabModel->revertAll(); // 回滚
        return false;
    }

    bookMessageTabModel->select(); // 重新查询，更新模型
    return true;
}


bool IDatabase::deleteCurrentReaderFile()
{
    QModelIndex curIndex = theReaderFileSelection->currentIndex();
    if (!curIndex.isValid()) { // 检查是否选中行
        qDebug() << "未选中要删除的患者";
        QMessageBox::information(nullptr, "提示", "未选中要删除的读者档案");
        return false;
    }

    if (!readerFileTabModel->removeRow(curIndex.row())) { // 移除内存中的行
        qDebug() << "移除行失败：" << readerFileTabModel->lastError().text();
        return false;
    }

    if (!readerFileTabModel->submitAll()) { // 提交删除到数据库
        qDebug() << "删除提交失败：" << readerFileTabModel->lastError().text();
        readerFileTabModel->revertAll(); // 回滚
        return false;
    }

    readerFileTabModel->select(); // 重新查询，更新模型
    return true;
}









bool IDatabase::submitBookMessageEdit()
{
    return bookMessageTabModel->submitAll();
}

void IDatabase::revertBookMessageEdit()
{

    bookMessageTabModel->revertAll();
}


bool IDatabase::submitReaderFileEdit()
{
    return readerFileTabModel->submitAll();
}

void IDatabase::revertReaderFileEdit()
{

    readerFileTabModel->revertAll();
}

bool IDatabase::submitRecordEdit()
{
    return borrowRecordsTabModel->submitAll();
}
void IDatabase::revertRecordEdit()
{

    borrowRecordsTabModel->revertAll();
}

QString IDatabase::userLogin(QString userName, QString password)
{
    QSqlQuery query;
    query.prepare("select userName,passWord from user where userName= :userId");
    query.bindValue(":userId",userName);
    query.exec();
    if(query.first() && query.value("userName").isValid()){
        QString passwd=query.value("passWord").toString();
        if(passwd==password){
            qDebug()<<"loginOK";
            return "loginOK";
        }
        else{
            qDebug()<<"wrongPassword";
            return "wrongPassword";
        }
    }
    else{
        qDebug()<<"no such user";
        return "wrongUsername";
    }
}

IDatabase::IDatabase(QObject *parent)
    : QObject{parent}
{
    initDatabase();
}






QSqlQuery IDatabase::getOverdueRecords(const QString &filter) {
    if (!borrowRecordsTabModel) {
        return QSqlQuery();
    }

    QSqlQuery query(borrowRecordsTabModel->database());
    query.prepare("SELECT * FROM borrow_records WHERE " + filter);
    query.exec();

    return query;
}


// #include "idatabase.h"

// IDatabase::IDatabase(QObject *parent)
//     : QObject{parent}
// {

// }

#include "idatabase.h"
#include<QDebug>
#include<QUuid>




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
    qDebug() << "===== 初始化患者模型 =====";
    if (!database.isOpen()) { // 先检查数据库是否打开
        qDebug() << "数据库未打开，初始化模型失败";
        return false;
    }
    bookMessageTabModel=new QSqlTableModel(this,database);
    qDebug() << "bookMessageTabModel 创建：" << bookMessageTabModel; // 打印指针地址，若为0则崩溃
    bookMessageTabModel->setTable("books");
    qDebug() << "设置表为patient：" << bookMessageTabModel->lastError().text();
    bookMessageTabModel->setEditStrategy(QSqlTableModel ::OnManualSubmit);
    bookMessageTabModel->setSort(bookMessageTabModel->fieldIndex("name"),Qt::AscendingOrder);
    qDebug() << "排序字段：" << bookMessageTabModel->fieldIndex("name"); // 若为-1，说明字段名错误
    if(!(bookMessageTabModel->select())) {
        qDebug() << "查询patient表失败：" << bookMessageTabModel->lastError().text();
        return false;
    }
    theBookMessageSelection=new QItemSelectionModel(bookMessageTabModel);
    qDebug() << "theBookMessageSelection 创建：" << theBookMessageSelection;
    return true;
}



int IDatabase::addNewBookMessage()
{
    bookMessageTabModel->insertRow(bookMessageTabModel->rowCount(),
                               QModelIndex());
    QModelIndex curIndex=bookMessageTabModel->index(bookMessageTabModel->rowCount()-1,
                                                  1);

    int curRecNo=curIndex.row();
    QSqlRecord curRec=bookMessageTabModel->record(curRecNo);
    // curRec.setValue("CREATEDTIMESAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("book_id",QUuid::createUuid().toString(QUuid::WithoutBraces));
    bookMessageTabModel->setRecord(curRecNo,curRec);
    return curIndex.row();

}



bool IDatabase::searchBookMessage(QString filter)
{
    bookMessageTabModel->setFilter(filter);
    bool ok = bookMessageTabModel->select(); // 应用过滤并重新查询
    if (!ok) {
        qDebug() << "查询失败：" << bookMessageTabModel->lastError().text();
    }
    return ok;
}



bool IDatabase::deleteCurrentBookMessage()
{
    QModelIndex curIndex = theBookMessageSelection->currentIndex();
    if (!curIndex.isValid()) { // 检查是否选中行
        qDebug() << "未选中要删除的患者";
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











bool IDatabase::submitBookMessageEdit()
{
    return bookMessageTabModel->submitAll();
}

void IDatabase::revertBookMessageEdit()
{

    bookMessageTabModel->revertAll();
}


// QString IDatabase::userLogin(QString userName, QString password)
// {
//     QSqlQuery query;
//     query.prepare("select username,password from user where username= :ID");
//     query.bindValue(":ID",userName);
//     query.exec();
//     if(query.first() && query.value("username").isValid()){
//         QString passwd=query.value("password").toString();
//         if(passwd==password){
//             qDebug()<<"loginOK";
//             return "loginOK";
//         }
//         else{
//             qDebug()<<"wrongPassword";
//             return "wrongPassword";
//         }
//     }
//     else{
//         qDebug()<<"no such user";
//         return "wrongUsername";
//     }
// }

IDatabase::IDatabase(QObject *parent)
    : QObject{parent}
{
    initDatabase();
}






#include "overduechecker.h"
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>
#include <QSqlError>

OverdueChecker::OverdueChecker(QObject *parent) : QThread(parent)
{
    m_running = true;
}

void OverdueChecker::stop()
{
    m_running = false;
    wait();
}

void OverdueChecker::run()
{

     qDebug() << "逾期检查线程启动";
    // 在线程内部创建数据库连接
       QSqlDatabase db;
     // 每个线程需要独立的连接名称
     QString connectionName = QString("overdue_checker_%1").arg((quintptr)this);

     if (QSqlDatabase::contains(connectionName)) {
         db = QSqlDatabase::database(connectionName);
     } else {
         db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
     }

    // 使用和主线程相同的数据库文件路径
    db.setDatabaseName("C:\\Users\\cd050\\Desktop\\QTHomeWork\\CourseHomework\\book_system.db");

    if (!db.open()) {
        qDebug() << "OverdueChecker: 打开数据库失败：" << db.lastError().text();
        return;
    }

    qDebug()<<"数据库连接成功";

    while (m_running) {
        // 检查逾期记录
        checkOverdueRecords(db);

        // 每30秒检查一次
        for (int i = 0; i < 30 && m_running; ++i) {
            sleep(1); // 休眠1秒
        }
    }

    db.close();

    QSqlDatabase::removeDatabase(connectionName);

    qDebug() << "逾期检查线程结束";
}

void OverdueChecker::checkOverdueRecords(QSqlDatabase &db)
{


    QSqlQuery testQuery(db);
    if (!testQuery.exec("SELECT 1")) {
        qDebug() << "OverdueChecker: 测试查询失败，数据库可能未连接";
        return;
    }



    QDateTime current = QDateTime::currentDateTime();


    QSqlQuery query(db);








    // 方法1：使用JOIN查询（更准确，可以获取最新的读者和图书信息）
    QString sql = "SELECT "
                  "br.record_id, "
                  "COALESCE(r.name, br.readerName) as reader_name, "
                  "COALESCE(b.name, br.bookName) as book_name, "
                  "br.due_time, "
                  "br.is_returned "
                  "FROM borrow_records br "
                  "LEFT JOIN readers r ON br.reader_id = r.reader_id "
                  "LEFT JOIN books b ON br.book_id = b.book_id "
                  "WHERE br.is_returned = 0 "  // 未归还
                  "AND date(br.due_time) < date('now')";  // 已逾期

    query.prepare(sql);

    if (!query.exec()) {
        qDebug() << "OverdueChecker: JOIN查询失败：" << query.lastError().text();
    }





    while (query.next()) {
        int recordId = query.value("record_id").toInt();
        QString readerName = query.value("reader_name").toString();
        QString bookName = query.value("book_name").toString();
        QDateTime dueDate = query.value("due_time").toDateTime();

        qDebug() << "发现逾期记录: 读者" << readerName
                 << ", 图书" << bookName
                 << ", 应还日期" << dueDate;

        // 发送逾期信号
        emit overdueFound(recordId, readerName, bookName, dueDate);
    }
}

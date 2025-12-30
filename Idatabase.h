#ifndef IDATABASE_H
#define IDATABASE_H

#include <QObject>
#include<QtSql>
#include<QSqlDatabase>
#include<QDataWidgetMapper>


class IDatabase : public QObject
{
    Q_OBJECT
public:
    static IDatabase &getInstance(){
        static IDatabase instance;
        return instance;
    }

    // 禁用拷贝构造和赋值
    IDatabase(const IDatabase&) = delete;
    IDatabase& operator=(const IDatabase&) = delete;

    // 成员变量声明（需public或提供getter）
    //图书信息表
    QSqlTableModel *bookMessageTabModel = nullptr;
    QItemSelectionModel *theBookMessageSelection = nullptr;

    //借阅记录表
    QSqlTableModel *borrowRecordsTabModel = nullptr;
    QItemSelectionModel *theborrowRecordsSelection = nullptr;

    //读者档案模型
    QSqlTableModel *readerFileTabModel = nullptr;
    QItemSelectionModel *theReaderFileSelection = nullptr;


    QString userLogin(QString userName,QString password);

private:
    explicit IDatabase(QObject *parent = nullptr);
    QSqlDatabase database;
    void initDatabase();
public:
    //图书信息模型
    bool initBookMessageModel();

    int addNewBookMessage();
    bool searchBookMessage(QString filter);
    bool deleteCurrentBookMessage();
    bool submitBookMessageEdit();
    void revertBookMessageEdit();

    //借阅信息模型
    bool initBorrowRecordsModel();

    bool searchBorrowRecords(QString filter);


    //读者档案模型
    bool initReaderFileModel();

    int addNewReaderFile();
    bool searchReaderFile(QString filter);
    bool deleteCurrentReaderFile();
    bool submitReaderFileEdit();
    void revertReaderFileEdit();

signals:



};

#endif // IDATABASE_H

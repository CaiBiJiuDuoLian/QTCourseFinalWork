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


    //借还书记录模型
    //QSqlTableModel *borrowRecordTabModel = nullptr;
    //QItemSelectionModel *theRecordSelection = nullptr;

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


    int addNewBorrowRecord();                  //借书
    bool searchRecord(QString filter);   //查找
    bool submitRecordEdit();             //保存到数据库
    void revertRecordEdit();
    //那么我想要还书该如何操作呢，我应该获取焦点，然后将is_returned字段设置为1，不删除


    //读者档案模型
    bool initReaderFileModel();

    int addNewReaderFile();
    bool searchReaderFile(QString filter);
    bool deleteCurrentReaderFile();
    bool submitReaderFileEdit();
    void revertReaderFileEdit();

    //借还书记录模型




    //1.1测试豆包代码
  QSqlQuery getOverdueRecords(const QString &filter);

signals:



};

#endif // IDATABASE_H

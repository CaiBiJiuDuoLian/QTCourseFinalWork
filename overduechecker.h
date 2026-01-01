// #ifndef OVERDUECHECKER_H
// #define OVERDUECHECKER_H

// #include <QObject>

// class overduemanager : public QObject
// {
//     Q_OBJECT
// public:
//     explicit overduemanager(QObject *parent = nullptr);

// signals:
// };

// #endif // OVERDUECHECKER_H


#ifndef OVERDUECHECKER_H
#define OVERDUECHECKER_H

#include <QThread>
#include <QDateTime>
#include<QSqlDatabase>

class OverdueChecker : public QThread
{
    Q_OBJECT
public:
    explicit OverdueChecker(QObject *parent = nullptr);

    void stop();

protected:
    void run() override;

 private:
    bool m_running;

void checkOverdueRecords(QSqlDatabase &db);

signals:
    void overdueFound(int recordId, const QString &readerName,
                      const QString &bookName, const QDateTime &dueDate);
};

#endif // OVERDUECHECKER_H

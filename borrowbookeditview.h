#ifndef BORROWBOOKEDITVIEW_H
#define BORROWBOOKEDITVIEW_H

#include <QWidget>
#include<QDataWidgetMapper>
namespace Ui {
class borrowBookEditView;
}

class borrowBookEditView : public QWidget
{
    Q_OBJECT

public:
    explicit borrowBookEditView(QWidget *parent = nullptr,int idx=0);
    ~borrowBookEditView();

private slots:
    void on_btBorrow_clicked();

    void on_btCancel_clicked();


    //12.31.00测试一下豆包代码
    void on_readerNameInput_textChanged(const QString &text); // 读者名输入变化时触发
    void on_bookNameInput_textChanged(const QString &text); // 书名输入变化时触发
    void queryReaderId(const QString &readerName); // 查询读者ID
    void queryBookId(const QString &bookName); // 查询图书ID

private:
    Ui::borrowBookEditView *ui;
    QDataWidgetMapper *dataMapper;

    //12.31.00测试一下豆包代码
    QTimer *readerQueryTimer; // 延迟查询定时器（避免输入抖动）
    QTimer *bookQueryTimer;   // 延迟查询定时器
signals:
    void goPreviousView();
};

#endif // BORROWBOOKEDITVIEW_H

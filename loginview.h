#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>

namespace Ui {
class loginView;
}

class loginView : public QWidget
{
    Q_OBJECT

public:
    explicit loginView(QWidget *parent = nullptr);
    ~loginView();

private slots:
    void on_btSignin_clicked();

private:
    Ui::loginView *ui;

signals:
    void LoginSuccess();
};

#endif // LOGINVIEW_H

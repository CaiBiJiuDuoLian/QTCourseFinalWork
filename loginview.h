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

private:
    Ui::loginView *ui;
};

#endif // LOGINVIEW_H

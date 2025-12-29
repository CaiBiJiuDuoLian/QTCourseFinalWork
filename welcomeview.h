#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <QWidget>

namespace Ui {
class WelcomeView;
}

class WelcomeView : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeView(QWidget *parent = nullptr);
    ~WelcomeView();

private slots:
    void on_btMessage_clicked();

    void on_btFile_clicked();

    void on_btRecord_clicked();

    void on_btSelect_clicked();

signals:
    void goBookMessageView();
    void goBorrowSelectView();
    void goRecordView();
    void goReaderFileView();

private:
    Ui::WelcomeView *ui;
};

#endif // WELCOMEVIEW_H

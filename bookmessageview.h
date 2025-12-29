#ifndef BOOKMESSAGEVIEW_H
#define BOOKMESSAGEVIEW_H

#include <QWidget>

namespace Ui {
class BookMessageView;
}

class BookMessageView : public QWidget
{
    Q_OBJECT

public:
    explicit BookMessageView(QWidget *parent = nullptr);
    ~BookMessageView();

private slots:
    void on_btAdd_clicked();

    void on_btSearch_clicked();

    void on_btDelete_clicked();

    void on_btEdit_clicked();

private:
    Ui::BookMessageView *ui;
signals:
    void goBookMessageEditView(int idx);
};

#endif // BOOKMESSAGEVIEW_H

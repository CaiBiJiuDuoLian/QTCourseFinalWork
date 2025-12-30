#ifndef RECORDVIEW_H
#define RECORDVIEW_H

#include <QWidget>

namespace Ui {
class RecordView;
}

class RecordView : public QWidget
{
    Q_OBJECT

public:
    explicit RecordView(QWidget *parent = nullptr);
    ~RecordView();

private slots:
    void on_btSearch_clicked();

    void on_btReturn_clicked();

    void on_btBorrow_clicked();

private:
    Ui::RecordView *ui;
signals:
    void goBorrowRecordsEditView(int idx);
};

#endif // RECORDVIEW_H

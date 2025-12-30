#ifndef READERFILEEDITVIEW_H
#define READERFILEEDITVIEW_H

#include <QWidget>
#include<QDataWidgetMapper>
namespace Ui {
class readerFileEditView;
}

class readerFileEditView : public QWidget
{
    Q_OBJECT

public:
    explicit readerFileEditView(QWidget *parent = nullptr,int idx=0);
    ~readerFileEditView();

private slots:
    void on_btSave_clicked();

    void on_btCancel_clicked();

private:
    Ui::readerFileEditView *ui;
    QDataWidgetMapper *dataMapper;

signals:
    void goPreviousView();
};

#endif // READERFILEEDITVIEW_H

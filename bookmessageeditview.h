#ifndef BOOKMESSAGEEDITVIEW_H
#define BOOKMESSAGEEDITVIEW_H

#include <QWidget>
#include<QDataWidgetMapper>
namespace Ui {
class bookMessageEditView;
}

class bookMessageEditView : public QWidget
{
    Q_OBJECT

public:
    explicit bookMessageEditView(QWidget *parent = nullptr, int idx=0);
    ~bookMessageEditView();

private slots:
    void on_btSave_clicked();

    void on_btCancel_clicked();

private:
    Ui::bookMessageEditView *ui;
    QDataWidgetMapper *dataMapper;

signals:
    void goPreviousView();
};

#endif // BOOKMESSAGEEDITVIEW_H

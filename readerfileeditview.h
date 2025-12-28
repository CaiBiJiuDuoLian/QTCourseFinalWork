#ifndef READERFILEEDITVIEW_H
#define READERFILEEDITVIEW_H

#include <QWidget>

namespace Ui {
class readerFileEditView;
}

class readerFileEditView : public QWidget
{
    Q_OBJECT

public:
    explicit readerFileEditView(QWidget *parent = nullptr);
    ~readerFileEditView();

private:
    Ui::readerFileEditView *ui;
};

#endif // READERFILEEDITVIEW_H

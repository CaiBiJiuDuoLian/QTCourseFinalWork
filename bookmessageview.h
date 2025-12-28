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

private:
    Ui::BookMessageView *ui;
};

#endif // BOOKMESSAGEVIEW_H

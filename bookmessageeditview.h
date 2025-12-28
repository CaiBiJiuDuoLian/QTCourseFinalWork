#ifndef BOOKMESSAGEEDITVIEW_H
#define BOOKMESSAGEEDITVIEW_H

#include <QWidget>

namespace Ui {
class bookMessageEditView;
}

class bookMessageEditView : public QWidget
{
    Q_OBJECT

public:
    explicit bookMessageEditView(QWidget *parent = nullptr);
    ~bookMessageEditView();

private:
    Ui::bookMessageEditView *ui;
};

#endif // BOOKMESSAGEEDITVIEW_H

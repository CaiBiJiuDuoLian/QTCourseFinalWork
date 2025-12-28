#ifndef BORROWBOOKEDITVIEW_H
#define BORROWBOOKEDITVIEW_H

#include <QWidget>

namespace Ui {
class borrowBookEditView;
}

class borrowBookEditView : public QWidget
{
    Q_OBJECT

public:
    explicit borrowBookEditView(QWidget *parent = nullptr);
    ~borrowBookEditView();

private:
    Ui::borrowBookEditView *ui;
};

#endif // BORROWBOOKEDITVIEW_H

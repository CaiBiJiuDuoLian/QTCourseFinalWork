#ifndef BORROWSELECT_H
#define BORROWSELECT_H

#include <QWidget>

namespace Ui {
class BorrowSelect;
}

class BorrowSelect : public QWidget
{
    Q_OBJECT

public:
    explicit BorrowSelect(QWidget *parent = nullptr);
    ~BorrowSelect();

private:
    Ui::BorrowSelect *ui;
};

#endif // BORROWSELECT_H

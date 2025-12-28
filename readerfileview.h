#ifndef READERFILEVIEW_H
#define READERFILEVIEW_H

#include <QWidget>

namespace Ui {
class ReaderFileView;
}

class ReaderFileView : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderFileView(QWidget *parent = nullptr);
    ~ReaderFileView();

private:
    Ui::ReaderFileView *ui;
};

#endif // READERFILEVIEW_H

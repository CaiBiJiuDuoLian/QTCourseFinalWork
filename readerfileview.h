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

private slots:
    void on_btSearch_clicked();

    void on_btAdd_clicked();

    void on_btDelete_clicked();

    void on_btEdit_clicked();

private:
    Ui::ReaderFileView *ui;
signals:
    void goReaderFileEditView(int idx);
};

#endif // READERFILEVIEW_H

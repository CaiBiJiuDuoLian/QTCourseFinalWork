#include "readerfileview.h"
#include "ui_readerfileview.h"

ReaderFileView::ReaderFileView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReaderFileView)
{
    ui->setupUi(this);
}

ReaderFileView::~ReaderFileView()
{
    delete ui;
}

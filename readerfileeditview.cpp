#include "readerfileeditview.h"
#include "ui_readerfileeditview.h"

readerFileEditView::readerFileEditView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::readerFileEditView)
{
    ui->setupUi(this);
}

readerFileEditView::~readerFileEditView()
{
    delete ui;
}

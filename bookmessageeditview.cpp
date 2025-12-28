#include "bookmessageeditview.h"
#include "ui_bookmessageeditview.h"

bookMessageEditView::bookMessageEditView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::bookMessageEditView)
{
    ui->setupUi(this);
}

bookMessageEditView::~bookMessageEditView()
{
    delete ui;
}

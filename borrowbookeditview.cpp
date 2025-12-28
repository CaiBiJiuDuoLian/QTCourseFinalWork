#include "borrowbookeditview.h"
#include "ui_borrowbookeditview.h"

borrowBookEditView::borrowBookEditView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::borrowBookEditView)
{
    ui->setupUi(this);
}

borrowBookEditView::~borrowBookEditView()
{
    delete ui;
}

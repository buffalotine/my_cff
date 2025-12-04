#include "notimplementview.h"
#include "ui_notimplementview.h"

NotImplementView::NotImplementView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NotImplementView)
{
    ui->setupUi(this);
}

NotImplementView::~NotImplementView()
{
    delete ui;
}

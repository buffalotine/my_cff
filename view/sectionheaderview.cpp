#include "sectionheaderview.h"
#include "ui_sectionheaderview.h"

SectionHeaderView::SectionHeaderView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SectionHeaderView)
{
    ui->setupUi(this);

    // 设置初始比例
    ui->splitter->setSizes({600, 100, 600});

}

SectionHeaderView::~SectionHeaderView()
{
    delete ui;
}

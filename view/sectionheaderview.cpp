#include <QMenu>

#include "sectionheaderview.h"
#include "ui_sectionheaderview.h"
#include "utils/logger.h"

SectionHeaderView::SectionHeaderView(QWidget *parent) : QWidget(parent) , ui(new Ui::SectionHeaderView)
{
    ui->setupUi(this);

    // 设置初始比例
    ui->splitter->setSizes({600, 100, 600});

    // 初始化表格样式
    initTableHeader();

    buildContextMenu();
}

SectionHeaderView::~SectionHeaderView()
{
    delete ui;
}

void SectionHeaderView::initTableHeader()
{
    // 设置列
    QStringList headers;
    headers << "Name"
            << "Virtual Size"
            << "Virtual Address"
            << "Raw Size"
            << "Raw Address"
            << "Characteristics";

    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // 最后一列自动拉伸
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    // 平均分配列宽
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // 隐藏垂直行号
    ui->tableWidget->verticalHeader()->setVisible(false);
    // 选中整行
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // 禁止编辑
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 允许交替行颜色
    ui->tableWidget->setAlternatingRowColors(true);
}

void SectionHeaderView::addData(const PeSectionData &data)
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    // 创建居中的单元格
    auto createItem = [](const QString& text)
    {
        QTableWidgetItem* item = new QTableWidgetItem(text);
        item->setTextAlignment(Qt::AlignCenter);
        return item;
    };

    ui->tableWidget->setItem(row, 0, createItem(data.name));
    ui->tableWidget->setItem(row, 1, createItem(data.virtualSize));
    ui->tableWidget->setItem(row, 2, createItem(data.virtualAddress));
    ui->tableWidget->setItem(row, 3, createItem(data.rawSize));
    ui->tableWidget->setItem(row, 4, createItem(data.rawAddress));
    ui->tableWidget->setItem(row, 5, createItem(data.characteristics));
}

void SectionHeaderView::clearTable()
{
    ui->tableWidget->setRowCount(0);
}

void SectionHeaderView::showEvent(QShowEvent *event)
{
    emit reqUpdateData();
}

void SectionHeaderView::handleExpandSection()
{
    LOG_DEBUG(__FUNCTION__" is called");
}

void SectionHeaderView::handleAddSection()
{
    LOG_DEBUG(__FUNCTION__" is called");
}

bool SectionHeaderView::buildContextMenu()
{
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidget, &QTableWidget::customContextMenuRequested, this, &SectionHeaderView::showContextMenu);

    // 菜单选项
    QAction* expandSectionAction = new QAction("扩节", this);
    connect(expandSectionAction, &QAction::triggered, this, &SectionHeaderView::handleExpandSection);

    QAction* addSectionAction = new QAction("加节", this);
    connect(addSectionAction, &QAction::triggered, this, &SectionHeaderView::handleAddSection);

    // 创建菜单 添加选项
    QMenu *contextMenu = new QMenu(ui->tableWidget);

    contextMenu->addAction(expandSectionAction);
    contextMenu->addSeparator();

    contextMenu->addAction(addSectionAction);

    return true;
}

void SectionHeaderView::showContextMenu(const QPoint &pos)
{
    QMenu *menu = findChild<QMenu*>();
    if (menu)
    {
        menu->exec(ui->tableWidget->viewport()->mapToGlobal(pos));
    }
}



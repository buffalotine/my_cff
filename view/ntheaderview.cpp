#include <QHeaderView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSizePolicy>
#include <QAction>
#include <QMenu>
#include <QMap>
#include <QMessageBox>

#include "utils/logger.h"
#include "ntheaderview.h"


NtHeaderView::NtHeaderView(QWidget *parent) : QTableView(parent), parent(parent)
{
    LOG_DEBUG(__FUNCTION__" is called, parent:0x%p", parent);

    initTableHeader(4);
    initConnect();

}

NtHeaderView::~NtHeaderView()
{
    delete m_model;
}

void NtHeaderView::onClickTableRow(const QModelIndex& index)
{
}

void NtHeaderView::initConnect()
{
    connect(m_model, &QStandardItemModel::itemChanged, this, &NtHeaderView::onItemChanged);
}

void NtHeaderView::showEvent(QShowEvent *event)
{
    LOG_DEBUG(__FUNCTION__" is called");
    emit reqUpdateData();
}

bool NtHeaderView::initTableHeader(int nColumn)
{
    // n行m列
    QStandardItemModel *model = new QStandardItemModel(0, nColumn, this);

    model->setHeaderData(0, Qt::Horizontal, "Member");
    model->setHeaderData(1, Qt::Horizontal, "Offset");
    model->setHeaderData(2, Qt::Horizontal, "Size");
    model->setHeaderData(3, Qt::Horizontal, "Value");

    // 居中1: 0, 1, 2, 3 代表列索引
    model->setHeaderData(1, Qt::Horizontal, QVariant(Qt::AlignCenter), Qt::TextAlignmentRole);


    this->m_model = model;
    this->setModel(model);


    // 水平和垂直都设置为expand
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 居中2: 设置水平表头文字默认居中
    // this->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    // 行号
    this->verticalHeader()->setVisible(false);

    // 最后列自动拉伸
    this->horizontalHeader()->setStretchLastSection(true);
    // 平均
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // allow手动调整列宽 与平均互斥
    //this->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

    // allow sort
    this->setSortingEnabled(true);

    // 选中整行
    this->setSelectionBehavior(QAbstractItemView::SelectRows);

    // 禁止编辑
    // this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 允许双击或按回车键编辑
    this->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);

    return true;
}

void NtHeaderView::addData(const QString& member, const QString& offset, const QString& size, const QString& value, const QString& meaning)
{
    QList<QStandardItem*> rowItems;

    QStandardItem* itemMember = new QStandardItem(member);
    // 居中3
    itemMember->setTextAlignment(Qt::AlignCenter);
    itemMember->setFlags(itemMember->flags() & ~Qt::ItemIsEditable);
    rowItems << itemMember;

    QStandardItem* itemOffset = new QStandardItem(offset);
    itemOffset->setFlags(itemOffset->flags() & ~Qt::ItemIsEditable);
    rowItems << itemOffset;

    QStandardItem* itemSize = new QStandardItem(size);
    itemSize->setFlags(itemSize->flags() & ~Qt::ItemIsEditable);
    rowItems << itemSize;

    QStandardItem* itemValue = new QStandardItem(value);
    itemValue->setFlags(itemValue->flags() | Qt::ItemIsEditable | Qt::ItemIsEnabled);
    itemValue->setBackground(QColor(240, 255, 240));
    rowItems << itemValue;

    // 存入原始数据
    itemMember->setData(QVariant::fromValue(value), Qt::UserRole);

    this->m_model->appendRow(rowItems);
}

void NtHeaderView::clearTable()
{
    m_model->removeRows(0, m_model->rowCount());
}

void NtHeaderView::onItemChanged(QStandardItem *item)
{
    if (!item) return;

    // 只允许"value"修改
    if (item->column() == 3)
    {
        QString newValue = item->text();
        int row = item->row();

        // 获取对应的字段名称
        QStandardItem* memberItem = m_model->item(row, 0);
        QString memberName = memberItem ? memberItem->text() : "Unknown";

        QStandardItem* offsetItem = m_model->item(row, 1);
        QString offsetValueStr = offsetItem ? offsetItem->text() : "00000000";

        LOG_DEBUG(__FUNCTION__" Value changed! Row: %d, Member: %s, New Value: %s", row, memberName.toStdString().c_str(), offsetValueStr.toStdString().c_str(), newValue.toStdString().c_str());

        emit reqModifyValueField(offsetValueStr, newValue);
    }
}


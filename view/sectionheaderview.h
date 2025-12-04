#ifndef SECTIONHEADERVIEW_H
#define SECTIONHEADERVIEW_H

#include <QWidget>
#include "service/pefileservice.h"

namespace Ui {
class SectionHeaderView;
}

class SectionHeaderView : public QWidget
{
    Q_OBJECT

public:
    explicit SectionHeaderView(QWidget *parent = nullptr);
    ~SectionHeaderView();

    // 初始化表头
    void initTableHeader();

    // 添加一行数据
    void addData(const PeSectionData& data);

    // 清空表格
    void clearTable();

signals:

    void reqUpdateData();

private:
    Ui::SectionHeaderView *ui;

public:
    void showEvent(QShowEvent *event) override;
    bool buildContextMenu();
    void showContextMenu(const QPoint &pos);

private slots:
    void handleExpandSection();
    void handleAddSection();


};

#endif // SECTIONHEADERVIEW_H

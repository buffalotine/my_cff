#ifndef NAVIGATIONVIEW_H
#define NAVIGATIONVIEW_H

#include <QTreeWidget>
#include "config/navigationconfig.h"

class NavigationView : public QTreeWidget
{
    Q_OBJECT

public:
    explicit NavigationView(QWidget *parent = nullptr);

    // 构建菜单
    void buildMenuTree(/*PEFile* peFile*/);

signals:
    // 当菜单项点击, 向外传递点击的配置项
    void navigationClicked(NavigationConfig item);

private slots:
    // 处理 TreeWidget 原生点击
    void onItemClicked(QTreeWidgetItem *item, int column);
};

#endif // NAVIGATIONVIEW_H

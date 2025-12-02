#include "navigationview.h"
#include <QHeaderView>
#include <QMap>

#include "utils/logger.h"

NavigationView::NavigationView(QWidget *parent) : QTreeWidget(parent)
{
    // 隐藏表头
    this->header()->setVisible(false);

    // 设置图标大小
    this->setIconSize(QSize(24, 24));

    this->setRootIsDecorated(false);

    // 连接原生点击信号到内部处理函数
    connect(this, &QTreeWidget::itemClicked, this, &NavigationView::onItemClicked);

    // 初始化构建
    buildMenuTree();
}
void NavigationView::buildMenuTree()
{
    this->clear();

    QMap<int, QTreeWidgetItem*> itemMap;

    // 获取所有配置项
    QList<NavigationConfig> allConfigs = NavigationConfig::values();


    // TODO 调用 PeFileUtil 类的实例, 区分dll/exe, 过滤掉特有的
    // if (peFileUtil.isExe())
    // {

    // }
    // else
    // {

    // }



    // 第一遍扫描创建所有节点
    for (const auto& config : allConfigs)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem();
            item->setText(0, config.getName());
            item->setIcon(0, QIcon(config.getIcon()));

            // 将Enum类型存入UserRole 以便点击时识别
            item->setData(0, Qt::UserRole, config.getType());

            itemMap[config.getType()] = item;
        }

    // 第二遍扫描建立父子关系
    for (const auto& config : allConfigs)
        {
            if (!itemMap.contains(config.getType())) continue;

            QTreeWidgetItem* currentItem = itemMap[config.getType()];
            int parentType = config.getParentType();

            // 顶层
            if (parentType == PAGE_TOP)
            {
                this->addTopLevelItem(currentItem);
            }
            else
            {
                if (itemMap.contains(parentType))
                {
                    itemMap[parentType]->addChild(currentItem);
                }
                else
                {
                    // 如果找不到父亲，默认作为顶层放入
                    this->addTopLevelItem(currentItem);
                }
            }
        }

    // 全部展开
    this->expandAll();
}

void NavigationView::onItemClicked(QTreeWidgetItem *item, int column)
{
    // 取出枚举值
    int type = item->data(0, Qt::UserRole).toInt();

    LOG_DEBUG(__FUNCTION__" raw controls click, column: %d", column)

    // 找到原始的Config对象
    QList<NavigationConfig> allConfigs = NavigationConfig::values();
    for (const auto& config : allConfigs)
    {
        if (config.getType() == type)
        {
            // 发送自定义信号
            emit navigationClicked(config);
            return;
        }
    }
}




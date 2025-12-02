#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils/logger.h"
#include "view/dosheaderview.h"
#include "view/notimplementview.h"
// #include "view/studentmanagerview.h"
// #include "view/classmanagerview.h"
// #include "view/coursemanagerview.h"
// #include "view/studentcoursemanagerview.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->mainSplitter->setSizes({188, 800});

    initSlotConnect();
    initRouter();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete stackedWidget;
}


void MainWindow::initSlotConnect()
{
    connect(ui->navigationView, &NavigationView::navigationClicked, this, &MainWindow::handleNavigationClicked);
}

void MainWindow::initRouter(/*const QString& filePath*/) // 或者传入 PE结构体
{
    QString filePath = "E:\\cracker\\phase3\\PE\\homework\\question\\PE01\\01\\Hello\\Hello.exe";

    if (!stackedWidget)
    {
        QWidget* contentContainer = ui->subViewContainer;
        QHBoxLayout* contentLayout = new QHBoxLayout(contentContainer);
        stackedWidget = new QStackedWidget(contentContainer);
        contentLayout->addWidget(stackedWidget);
    }

    // 1. 清空旧数据
    stackedWidget->blockSignals(true);
    // 移除并删除所有旧 View
    while (stackedWidget->count() > 0)
    {
        QWidget* w = stackedWidget->widget(0);
        stackedWidget->removeWidget(w);
        delete w;
    }

    viewCache.clear();

    // 2. 根据 PE 文件内容，动态生成左侧菜单
    // 这一步在 NavigationListView 内部做，传入 PE 数据，
    // 它会根据数据是否存在(DataDirectory)来决定 add 哪些 item。
    ui->navigationView->buildMenuTree(/*filePath*/);

    stackedWidget->blockSignals(false);
}

// 槽函数：点击左侧菜单时触发
void MainWindow::handleNavigationClicked(NavigationConfig item)
{
    NavigationItemTyPeEnum type = item.getType();

    // 1. 检查缓存中是否已经创建了这个 View
    if (viewCache.contains(type))
    {
        stackedWidget->setCurrentWidget(viewCache[type]);
        return;
    }

    // 2. 如果没创建（懒加载），现在创建
    QWidget* newView = nullptr;

    switch (type)
    {
        case PAGE_DOS_HEADER:
        {
            auto newViewTemp = new DosHeaderView();
            // newViewTemp->addData("e_magic", "00000000", "Word", "5A4D");
            newView = newViewTemp;
            break;
        }


        default:
            LOG_DEBUG(__FUNCTION__" Unknown type or not implemented: %d", type);
            newView = new NotImplementView();
        }

    if (newView)
    {
        // 3. 加入 Stack 和 缓存
        stackedWidget->addWidget(newView);
        viewCache.insert(type, newView);

        // 4. 切换显示
        stackedWidget->setCurrentWidget(newView);
    }
}




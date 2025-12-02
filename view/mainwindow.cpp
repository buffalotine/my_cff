#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils/logger.h"
// #include "view/homeview.h"
// #include "view/studentmanagerview.h"
// #include "view/classmanagerview.h"
// #include "view/coursemanagerview.h"
// #include "view/studentcoursemanagerview.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
        stackedWidget = new QStackedWidget();
    }

    // 1. 清空旧数据
    stackedWidget->blockSignals(true); // 防止抖动
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
        // case PAGE_DOS_HEADER:
        //     // newView = new HomeView(); // 假设这是 Dos Header View
        //     // newView->setData(peFile->getDosHeader()); // 传入数据
        //     break;
        // case PAGE_NT_HEADERS:
        //     // NT Headers 通常只是父节点，可能不需要 View，或者是摘要 View
        //     // newView = new QWidget();
        //     break;
        // case PAGE_IMPORT_DIRECTORY:
        //     // newView = new ClassManagerView(); // 替换为 ImportView
        //     break;
        // ... 其他 case
        default:
            LOG_DEBUG(__FUNCTION__" Unknown type or not implemented: %d", type);
            return;
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




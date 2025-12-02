#include <QMessageBox>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils/logger.h"
#include "view/dosheaderview.h"
#include "view/fileheaderview.h"
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
    // initRouter();
}

MainWindow::~MainWindow()
{
    peFileService.closePeFile();
    delete ui;
    delete stackedWidget;
}


void MainWindow::initSlotConnect()
{
    connect(ui->actionopen, &QAction::triggered, this, &MainWindow::onActionOpenTriggered);
    connect(ui->actionclose, &QAction::triggered, this, &MainWindow::onActionCloseTriggered);
    connect(ui->actionexit, &QAction::triggered, this, &MainWindow::onActionExitTriggered);

    connect(ui->navigationView, &NavigationView::navigationClicked, this, &MainWindow::handleNavigationClicked);
    connect(&peFileService, &PeFileService::reqAfterLoadPeFileSuc,
            [this](const QString& fileName)
            {
                ui->statusbar->showMessage("load file " + fileName);
            }
    );
    connect(&peFileService, &PeFileService::reqAfterClosePeFileSuc,
            [this]()
            {
                ui->statusbar->showMessage("close file");
            }
            );
}

void MainWindow::initRouter(const QString& fileName)
{

    if (!stackedWidget)
    {
        QWidget* contentContainer = ui->subViewContainer;
        QHBoxLayout* contentLayout = new QHBoxLayout(contentContainer);
        stackedWidget = new QStackedWidget(contentContainer);
        contentLayout->addWidget(stackedWidget);
    }

    // 1. 清空旧数据
    stackedWidget->blockSignals(true);
    // 移除
    while (stackedWidget->count() > 0)
    {
        QWidget* w = stackedWidget->widget(0);
        stackedWidget->removeWidget(w);
        delete w;
    }

    viewCache.clear();

    // 2. 根据 PE 动态生成左侧菜单 TODO 这里需要补一个逻辑
    bool isDll = false;
    if (fileName.endsWith(".dll", Qt::CaseInsensitive))
    {
        isDll = true;
    }

    if (peFileService.loadPeFile(fileName))
    {
        LOG_INFO(__FUNCTION__" PE File loaded.");
    }
    else
    {
        LOG_ERROR(__FUNCTION__" Failed to load PE File.");
        QMessageBox::critical(this, "51asm", "invalid file");
        return;
    }


    ui->navigationView->buildMenuTree(isDll);

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

            connect(newViewTemp, &DosHeaderView::reqModifyDosHeaderValueField, [this, newViewTemp](const QString& offsetStr, const QString& newValue)
                    {
                        if (!this->peFileService.writeHexData(offsetStr, newValue))
                        {
                            QMessageBox::critical(this, "51asm", "modify failed");
                        }

                        newViewTemp->showEvent(nullptr);

                    });

            connect(newViewTemp, &DosHeaderView::reqUpdateData, [this, newViewTemp]()
                    {
                        auto v = peFileService.getDosHeaderData();
                        newViewTemp->clearTable();
                        for (const auto& e : v)
                        {
                            newViewTemp->addData(e.member, e.offset, e.size, e.value);
                        }
                    });



            newView = newViewTemp;
            break;
        }

        case PAGE_FILE_HEADER:
        {
            auto newViewTemp = new FileHeaderView();

            connect(newViewTemp, &FileHeaderView::reqModifyValueField, [this, newViewTemp](const QString& offsetStr, const QString& newValue)
                    {
                        if (!this->peFileService.writeHexData(offsetStr, newValue))
                        {
                            QMessageBox::critical(this, "51asm", "modify failed");
                        }

                        newViewTemp->showEvent(nullptr);

                    });

            connect(newViewTemp, &FileHeaderView::reqUpdateData, [this, newViewTemp]()
                    {
                        auto v = peFileService.getFileHeaderData();
                        newViewTemp->clearTable();
                        for (const auto& e : v)
                        {
                            newViewTemp->addData(e.member, e.offset, e.size, e.value, e.meaning);
                        }
                    });



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

// 点击打开
void MainWindow::onActionOpenTriggered()
{
    // 如果当前有文件，先关闭
    if (peFileService.isValid())
    {
        peFileService.closePeFile();
    }

    // 弹出文件选择框
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open PE File"),
        "",
        tr("Executable Files (*.exe *.dll *.sys *.ocx);;All Files (*)")
        );

    if (fileName.isEmpty())
    {
        return;
    }

    initRouter(fileName);
}

// 点击关闭
void MainWindow::onActionCloseTriggered()
{
    peFileService.closePeFile();

    // 清理界面
    ui->navigationView->clear();
    while (stackedWidget && stackedWidget->count() > 0)
    {
        QWidget* w = stackedWidget->widget(0);
        stackedWidget->removeWidget(w);
        delete w;
    }

    viewCache.clear();
}

// 点击退出
void MainWindow::onActionExitTriggered()
{
    // 关闭前清理
    peFileService.closePeFile();
    QApplication::quit();
}


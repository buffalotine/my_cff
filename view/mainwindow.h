#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "config/navigationconfig.h"
#include "service/pefileservice.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void handleNavigationClicked(NavigationConfig item);
    void onActionOpenTriggered();
    void onActionCloseTriggered();
    void onActionExitTriggered();

private:
    Ui::MainWindow *ui;
    void initSlotConnect();
    void initRouter(const QString& fileName);
    QStackedWidget* stackedWidget = nullptr;
    QMap<int, QWidget*> viewCache;
    PeFileService peFileService;
};
#endif // MAINWINDOW_H

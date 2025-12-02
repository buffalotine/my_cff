#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "config/navigationconfig.h"

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


private:
    Ui::MainWindow *ui;
    void initSlotConnect();
    void initRouter();
    QStackedWidget* stackedWidget = nullptr;
    QMap<int, QWidget*> viewCache;
};
#endif // MAINWINDOW_H

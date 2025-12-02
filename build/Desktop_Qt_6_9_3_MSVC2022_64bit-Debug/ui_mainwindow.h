/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "view/navigationview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionopen;
    QAction *actionclose;
    QAction *actionexit;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *mainSplitter;
    NavigationView *navigationView;
    QGroupBox *subViewContainer;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1231, 660);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/images/icon/navigation/m8.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        actionopen = new QAction(MainWindow);
        actionopen->setObjectName("actionopen");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/images/icon/menu/13.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionopen->setIcon(icon1);
        actionclose = new QAction(MainWindow);
        actionclose->setObjectName("actionclose");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/images/icon/menu/14.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionclose->setIcon(icon2);
        actionexit = new QAction(MainWindow);
        actionexit->setObjectName("actionexit");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/images/icon/menu/33.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionexit->setIcon(icon3);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        mainSplitter = new QSplitter(centralWidget);
        mainSplitter->setObjectName("mainSplitter");
        mainSplitter->setLineWidth(1);
        mainSplitter->setMidLineWidth(0);
        mainSplitter->setOrientation(Qt::Orientation::Horizontal);
        mainSplitter->setOpaqueResize(true);
        navigationView = new NavigationView(mainSplitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        navigationView->setHeaderItem(__qtreewidgetitem);
        navigationView->setObjectName("navigationView");
        mainSplitter->addWidget(navigationView);
        navigationView->header()->setVisible(false);
        subViewContainer = new QGroupBox(mainSplitter);
        subViewContainer->setObjectName("subViewContainer");
        mainSplitter->addWidget(subViewContainer);

        horizontalLayout->addWidget(mainSplitter);

        MainWindow->setCentralWidget(centralWidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1231, 22));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(actionopen);
        menu->addAction(actionclose);
        menu->addSeparator();
        menu->addAction(actionexit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MY CFF EXPLORER", nullptr));
        actionopen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200(&O)", nullptr));
        actionclose->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255(&C)", nullptr));
        actionexit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272(&E)", nullptr));
        subViewContainer->setTitle(QString());
        menu->setTitle(QCoreApplication::translate("MainWindow", "\360\237\223\202\346\226\207\344\273\266(&F)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

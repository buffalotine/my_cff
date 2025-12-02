/********************************************************************************
** Form generated from reading UI file 'notimplementview.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTIMPLEMENTVIEW_H
#define UI_NOTIMPLEMENTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NotImplementView
{
public:
    QGridLayout *gridLayout;
    QLabel *label;

    void setupUi(QWidget *NotImplementView)
    {
        if (NotImplementView->objectName().isEmpty())
            NotImplementView->setObjectName("NotImplementView");
        NotImplementView->resize(970, 647);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NotImplementView->sizePolicy().hasHeightForWidth());
        NotImplementView->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(NotImplementView);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(NotImplementView);
        label->setObjectName("label");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMaximumSize(QSize(2000, 2000));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/images/error_01.png")));
        label->setScaledContents(true);
        label->setWordWrap(false);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(NotImplementView);

        QMetaObject::connectSlotsByName(NotImplementView);
    } // setupUi

    void retranslateUi(QWidget *NotImplementView)
    {
        NotImplementView->setWindowTitle(QCoreApplication::translate("NotImplementView", "Form", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class NotImplementView: public Ui_NotImplementView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTIMPLEMENTVIEW_H

/********************************************************************************
** Form generated from reading UI file 'imageregistration.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEREGISTRATION_H
#define UI_IMAGEREGISTRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageRegistrationClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ImageRegistrationClass)
    {
        if (ImageRegistrationClass->objectName().isEmpty())
            ImageRegistrationClass->setObjectName(QStringLiteral("ImageRegistrationClass"));
        ImageRegistrationClass->resize(600, 400);
        menuBar = new QMenuBar(ImageRegistrationClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ImageRegistrationClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ImageRegistrationClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ImageRegistrationClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ImageRegistrationClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ImageRegistrationClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ImageRegistrationClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ImageRegistrationClass->setStatusBar(statusBar);

        retranslateUi(ImageRegistrationClass);

        QMetaObject::connectSlotsByName(ImageRegistrationClass);
    } // setupUi

    void retranslateUi(QMainWindow *ImageRegistrationClass)
    {
        ImageRegistrationClass->setWindowTitle(QApplication::translate("ImageRegistrationClass", "ImageRegistration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImageRegistrationClass: public Ui_ImageRegistrationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEREGISTRATION_H

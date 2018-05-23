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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageRegistrationClass
{
public:
    QAction *action_open_reference_image;
    QAction *action_open_target_image;
    QAction *action_run;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *image_r;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *image_t;
    QLabel *label_4;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ImageRegistrationClass)
    {
        if (ImageRegistrationClass->objectName().isEmpty())
            ImageRegistrationClass->setObjectName(QStringLiteral("ImageRegistrationClass"));
        ImageRegistrationClass->resize(1052, 555);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ImageRegistrationClass->sizePolicy().hasHeightForWidth());
        ImageRegistrationClass->setSizePolicy(sizePolicy);
        action_open_reference_image = new QAction(ImageRegistrationClass);
        action_open_reference_image->setObjectName(QStringLiteral("action_open_reference_image"));
        action_open_target_image = new QAction(ImageRegistrationClass);
        action_open_target_image->setObjectName(QStringLiteral("action_open_target_image"));
        action_run = new QAction(ImageRegistrationClass);
        action_run->setObjectName(QStringLiteral("action_run"));
        centralWidget = new QWidget(ImageRegistrationClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        image_r = new QLabel(centralWidget);
        image_r->setObjectName(QStringLiteral("image_r"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(image_r->sizePolicy().hasHeightForWidth());
        image_r->setSizePolicy(sizePolicy1);
        image_r->setMinimumSize(QSize(512, 0));
        image_r->setScaledContents(true);

        verticalLayout->addWidget(image_r);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        image_t = new QLabel(centralWidget);
        image_t->setObjectName(QStringLiteral("image_t"));
        sizePolicy1.setHeightForWidth(image_t->sizePolicy().hasHeightForWidth());
        image_t->setSizePolicy(sizePolicy1);
        image_t->setMinimumSize(QSize(512, 0));
        image_t->setScaledContents(true);

        verticalLayout_2->addWidget(image_t);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_4);


        horizontalLayout->addLayout(verticalLayout_2);

        ImageRegistrationClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(ImageRegistrationClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ImageRegistrationClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ImageRegistrationClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ImageRegistrationClass->setStatusBar(statusBar);

        mainToolBar->addAction(action_open_reference_image);
        mainToolBar->addAction(action_open_target_image);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_run);

        retranslateUi(ImageRegistrationClass);

        QMetaObject::connectSlotsByName(ImageRegistrationClass);
    } // setupUi

    void retranslateUi(QMainWindow *ImageRegistrationClass)
    {
        ImageRegistrationClass->setWindowTitle(QApplication::translate("ImageRegistrationClass", "ImageRegistration", nullptr));
        action_open_reference_image->setText(QApplication::translate("ImageRegistrationClass", "R", nullptr));
#ifndef QT_NO_TOOLTIP
        action_open_reference_image->setToolTip(QApplication::translate("ImageRegistrationClass", "Open reference image", nullptr));
#endif // QT_NO_TOOLTIP
        action_open_target_image->setText(QApplication::translate("ImageRegistrationClass", "T", nullptr));
#ifndef QT_NO_TOOLTIP
        action_open_target_image->setToolTip(QApplication::translate("ImageRegistrationClass", "Open target image", nullptr));
#endif // QT_NO_TOOLTIP
        action_run->setText(QApplication::translate("ImageRegistrationClass", "Run", nullptr));
#ifndef QT_NO_TOOLTIP
        action_run->setToolTip(QApplication::translate("ImageRegistrationClass", "Run registration", nullptr));
#endif // QT_NO_TOOLTIP
        image_r->setText(QString());
        label_2->setText(QApplication::translate("ImageRegistrationClass", "Reference image", nullptr));
        image_t->setText(QString());
        label_4->setText(QApplication::translate("ImageRegistrationClass", "Target image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImageRegistrationClass: public Ui_ImageRegistrationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEREGISTRATION_H

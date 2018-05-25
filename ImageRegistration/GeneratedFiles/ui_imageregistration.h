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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageRegistrationClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_5;
    QRadioButton *radio_translate;
    QRadioButton *radio_rotate;
    QRadioButton *radio_affine;
    QRadioButton *radio_perspective;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_6;
    QRadioButton *radio_l1;
    QRadioButton *radio_l2;
    QRadioButton *radio_linf;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_7;
    QRadioButton *radio_naive;
    QRadioButton *radio_ga;
    QVBoxLayout *verticalLayout_8;
    QPushButton *button_ref_img;
    QPushButton *button_tar_img;
    QSpacerItem *verticalSpacer;
    QPushButton *button_run;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *image_r;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *image_t;
    QLabel *label_4;
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
        centralWidget = new QWidget(ImageRegistrationClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setMinimumSize(QSize(140, 0));
        groupBox->setStyleSheet(QStringLiteral(""));
        groupBox->setFlat(false);
        verticalLayout_5 = new QVBoxLayout(groupBox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        radio_translate = new QRadioButton(groupBox);
        radio_translate->setObjectName(QStringLiteral("radio_translate"));
        radio_translate->setMinimumSize(QSize(0, 24));
        radio_translate->setChecked(true);

        verticalLayout_5->addWidget(radio_translate);

        radio_rotate = new QRadioButton(groupBox);
        radio_rotate->setObjectName(QStringLiteral("radio_rotate"));
        radio_rotate->setMinimumSize(QSize(0, 24));

        verticalLayout_5->addWidget(radio_rotate);

        radio_affine = new QRadioButton(groupBox);
        radio_affine->setObjectName(QStringLiteral("radio_affine"));
        radio_affine->setMinimumSize(QSize(0, 24));

        verticalLayout_5->addWidget(radio_affine);

        radio_perspective = new QRadioButton(groupBox);
        radio_perspective->setObjectName(QStringLiteral("radio_perspective"));
        radio_perspective->setMinimumSize(QSize(0, 24));

        verticalLayout_5->addWidget(radio_perspective);


        horizontalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        groupBox_2->setMinimumSize(QSize(140, 0));
        groupBox_2->setStyleSheet(QStringLiteral(""));
        groupBox_2->setFlat(false);
        verticalLayout_6 = new QVBoxLayout(groupBox_2);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        radio_l1 = new QRadioButton(groupBox_2);
        radio_l1->setObjectName(QStringLiteral("radio_l1"));
        radio_l1->setMinimumSize(QSize(0, 24));

        verticalLayout_6->addWidget(radio_l1);

        radio_l2 = new QRadioButton(groupBox_2);
        radio_l2->setObjectName(QStringLiteral("radio_l2"));
        radio_l2->setMinimumSize(QSize(0, 24));
        radio_l2->setChecked(true);

        verticalLayout_6->addWidget(radio_l2);

        radio_linf = new QRadioButton(groupBox_2);
        radio_linf->setObjectName(QStringLiteral("radio_linf"));
        radio_linf->setMinimumSize(QSize(0, 24));

        verticalLayout_6->addWidget(radio_linf);


        horizontalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        groupBox_3->setMinimumSize(QSize(140, 0));
        groupBox_3->setStyleSheet(QStringLiteral(""));
        groupBox_3->setFlat(false);
        verticalLayout_7 = new QVBoxLayout(groupBox_3);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        radio_naive = new QRadioButton(groupBox_3);
        radio_naive->setObjectName(QStringLiteral("radio_naive"));
        radio_naive->setMinimumSize(QSize(0, 24));
        radio_naive->setChecked(true);

        verticalLayout_7->addWidget(radio_naive);

        radio_ga = new QRadioButton(groupBox_3);
        radio_ga->setObjectName(QStringLiteral("radio_ga"));
        radio_ga->setMinimumSize(QSize(0, 24));

        verticalLayout_7->addWidget(radio_ga);

        radio_naive->raise();
        radio_naive->raise();
        radio_ga->raise();

        horizontalLayout_2->addWidget(groupBox_3);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        button_ref_img = new QPushButton(centralWidget);
        button_ref_img->setObjectName(QStringLiteral("button_ref_img"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(button_ref_img->sizePolicy().hasHeightForWidth());
        button_ref_img->setSizePolicy(sizePolicy2);
        button_ref_img->setMinimumSize(QSize(120, 0));

        verticalLayout_8->addWidget(button_ref_img);

        button_tar_img = new QPushButton(centralWidget);
        button_tar_img->setObjectName(QStringLiteral("button_tar_img"));
        sizePolicy2.setHeightForWidth(button_tar_img->sizePolicy().hasHeightForWidth());
        button_tar_img->setSizePolicy(sizePolicy2);
        button_tar_img->setMinimumSize(QSize(120, 0));

        verticalLayout_8->addWidget(button_tar_img);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer);

        button_run = new QPushButton(centralWidget);
        button_run->setObjectName(QStringLiteral("button_run"));
        sizePolicy2.setHeightForWidth(button_run->sizePolicy().hasHeightForWidth());
        button_run->setSizePolicy(sizePolicy2);
        button_run->setMinimumSize(QSize(120, 0));

        verticalLayout_8->addWidget(button_run);


        horizontalLayout_2->addLayout(verticalLayout_8);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        image_r = new QLabel(centralWidget);
        image_r->setObjectName(QStringLiteral("image_r"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(image_r->sizePolicy().hasHeightForWidth());
        image_r->setSizePolicy(sizePolicy3);
        image_r->setMinimumSize(QSize(512, 0));
        image_r->setStyleSheet(QStringLiteral("border: 1px solid #dcdcdc;"));
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
        sizePolicy3.setHeightForWidth(image_t->sizePolicy().hasHeightForWidth());
        image_t->setSizePolicy(sizePolicy3);
        image_t->setMinimumSize(QSize(512, 0));
        image_t->setStyleSheet(QStringLiteral("border: 1px solid #dcdcdc;"));
        image_t->setScaledContents(true);

        verticalLayout_2->addWidget(image_t);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_4);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout_4->addLayout(verticalLayout_3);

        ImageRegistrationClass->setCentralWidget(centralWidget);
        label_2->raise();
        statusBar = new QStatusBar(ImageRegistrationClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ImageRegistrationClass->setStatusBar(statusBar);

        retranslateUi(ImageRegistrationClass);

        QMetaObject::connectSlotsByName(ImageRegistrationClass);
    } // setupUi

    void retranslateUi(QMainWindow *ImageRegistrationClass)
    {
        ImageRegistrationClass->setWindowTitle(QApplication::translate("ImageRegistrationClass", "ImageRegistration", nullptr));
        groupBox->setTitle(QApplication::translate("ImageRegistrationClass", "Transform", nullptr));
        radio_translate->setText(QApplication::translate("ImageRegistrationClass", "Translate", nullptr));
        radio_rotate->setText(QApplication::translate("ImageRegistrationClass", "Rotate", nullptr));
        radio_affine->setText(QApplication::translate("ImageRegistrationClass", "Affine", nullptr));
        radio_perspective->setText(QApplication::translate("ImageRegistrationClass", "Perspective", nullptr));
        groupBox_2->setTitle(QApplication::translate("ImageRegistrationClass", "Similarity", nullptr));
        radio_l1->setText(QApplication::translate("ImageRegistrationClass", "L1", nullptr));
        radio_l2->setText(QApplication::translate("ImageRegistrationClass", "L2", nullptr));
        radio_linf->setText(QApplication::translate("ImageRegistrationClass", "L\342\210\236", nullptr));
        groupBox_3->setTitle(QApplication::translate("ImageRegistrationClass", "Optimization Method", nullptr));
        radio_naive->setText(QApplication::translate("ImageRegistrationClass", "Brute Force", nullptr));
        radio_ga->setText(QApplication::translate("ImageRegistrationClass", "GA", nullptr));
        button_ref_img->setText(QApplication::translate("ImageRegistrationClass", "Reference Image", nullptr));
        button_tar_img->setText(QApplication::translate("ImageRegistrationClass", "Target Image", nullptr));
        button_run->setText(QApplication::translate("ImageRegistrationClass", "Run Registration", nullptr));
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

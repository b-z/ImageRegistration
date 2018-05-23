#include "stdafx.h"
#include "imageregistration.h"
#include <opencv2\opencv.hpp>

ImageRegistration::ImageRegistration(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    manager = new Manager(this);
    connect(ui.action_open_reference_image, SIGNAL(triggered()), manager, SLOT(loadReferenceImage()));
    connect(ui.action_open_target_image, SIGNAL(triggered()), manager, SLOT(loadTargetImage()));
    connect(ui.action_run, SIGNAL(triggered()), manager, SLOT(runSimpleRegistration()));
    connect(manager, SIGNAL(referenceImageReady()), this, SLOT(updateReferenceImage()));
    connect(manager, SIGNAL(targetImageReady()), this, SLOT(updateTargetImage()));
}

ImageRegistration::~ImageRegistration()
{ 

}

void ImageRegistration::updateReferenceImage() {
    QImage qimg;
    cv::Mat img = manager->ref_img;
    if (img.channels() == 3) {
        qimg = QImage((const unsigned char *)(img.data), img.cols, img.rows, img.cols * img.channels(), QImage::Format_RGB888);
    } else if (img.channels() == 1) {
        qimg = QImage((const unsigned char *)(img.data), img.cols, img.rows, img.cols * img.channels(), QImage::Format_ARGB32);
    } else {
        qimg = QImage((const unsigned char *)(img.data), img.cols, img.rows, img.cols * img.channels(), QImage::Format_RGB888);
    }
    if (!img.cols) return;
    ui.image_r->setFixedSize(512, img.rows * 512 / img.cols);
    ui.image_r->setPixmap(QPixmap::fromImage(qimg));
    adjustSize();
}

void ImageRegistration::updateTargetImage() {
    QImage qimg;
    cv::Mat img = manager->tar_img;
    if (img.channels() == 3) {
        qimg = QImage((const unsigned char *)(img.data), img.cols, img.rows, img.cols * img.channels(), QImage::Format_RGB888);
    }
    else if (img.channels() == 1) {
        qimg = QImage((const unsigned char *)(img.data), img.cols, img.rows, img.cols * img.channels(), QImage::Format_ARGB32);
    }
    else {
        qimg = QImage((const unsigned char *)(img.data), img.cols, img.rows, img.cols * img.channels(), QImage::Format_RGB888);
    }
    if (!img.cols) return;
    ui.image_t->setFixedSize(512, img.rows * 512 / img.cols);
    ui.image_t->setPixmap(QPixmap::fromImage(qimg));
    adjustSize();
}
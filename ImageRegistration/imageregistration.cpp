#include "stdafx.h"
#include "imageregistration.h"
#include <opencv2\opencv.hpp>
#include "ResultWindow.h"
#include "Registration.h"

ImageRegistration::ImageRegistration(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    result_window = new ResultWindow(this);
    manager = new Manager(this, result_window);
    connect(ui.button_ref_img, SIGNAL(clicked()), manager, SLOT(loadReferenceImage()));
    connect(ui.button_tar_img, SIGNAL(clicked()), manager, SLOT(loadTargetImage()));
    connect(ui.button_run, SIGNAL(clicked()), this, SLOT(runRegistration()));
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
    ui.image_r->setFixedSize(IMAGE_WIDTH, img.rows * IMAGE_WIDTH / img.cols);
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
    ui.image_t->setFixedSize(IMAGE_WIDTH, img.rows * IMAGE_WIDTH / img.cols);
    ui.image_t->setPixmap(QPixmap::fromImage(qimg));
    adjustSize();
    result_window->updateTargetImage(qimg);
}

void ImageRegistration::runRegistration() {
    Registration::TransformType t = Registration::TransformType::TRANSFORM_TRANSLATE;
    if (ui.radio_rotate->isChecked()) t = Registration::TransformType::TRANSFORM_ROTATE;
    if (ui.radio_affine->isChecked()) t = Registration::TransformType::TRANSFORM_AFFINE;
    if (ui.radio_perspective->isChecked()) t = Registration::TransformType::TRANSFORM_PERSPECTIVE;
    Registration::SimilarityType s = Registration::SimilarityType::SIMILARITY_L1;
    if (ui.radio_l2->isChecked()) s = Registration::SimilarityType::SIMILARITY_L2;
    if (ui.radio_linf->isChecked()) s = Registration::SimilarityType::SIMILARITY_LINF;
    Registration::OptimizationType o = Registration::OptimizationType::OPTIMIZE_NAIVE;
    if (ui.radio_ga->isChecked()) o = Registration::OptimizationType::OPTIMIZE_GA;
    manager->runRegistration(t, s, o);
}
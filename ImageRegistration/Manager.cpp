#include "stdafx.h"
#include "Manager.h"
#include <string>
#include <opencv2\opencv.hpp>
#include "Registration.h"

Manager::Manager(QObject *parent)
    : QObject(parent)
{

}

Manager::~Manager()
{

}

cv::Mat Manager::loadImage() {
    QString filename;
    while (filename.isEmpty()) {
        filename = QFileDialog::getOpenFileName(NULL, "Open image", "", "*.jpg *.png *.bnp", 0);
    }
    cv::Mat img = cv::imread(filename.toLocal8Bit().toStdString());
    if (img.channels() == 3) {
        cv::cvtColor(img, img, CV_BGR2RGB);
    }
    return img;
}

void Manager::loadReferenceImage() {
    ref_img = loadImage();
    emit referenceImageReady();
}

void Manager::loadTargetImage() {
    tar_img = loadImage();
    emit targetImageReady();
}

void Manager::runSimpleRegistration() {
    cv::Mat ref;
    cv::Mat tar;
    cv::resize(ref_img, ref, cv::Size(0, 0), 0.1, 0.1);
    cv::resize(tar_img, tar, cv::Size(0, 0), 0.1, 0.1);
    Registration r(this, ref, tar, Registration::TRANSFORM_TRANSLATE,
        Registration::SIMILARITY_L2, Registration::OPTIMIZE_NAIVE);
    r.runRegistration();
}
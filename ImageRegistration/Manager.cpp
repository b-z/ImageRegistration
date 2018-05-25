#include "stdafx.h"
#include "Manager.h"
#include <string>
#include <opencv2\opencv.hpp>
#include "RegistrationThread.h"
#include "ResultWindow.h"

Manager::Manager(QObject *parent, ResultWindow* r_window)
    : QObject(parent)
{
    result_window = r_window;
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

void Manager::runRegistration(Registration::TransformType t, Registration::SimilarityType s, Registration::OptimizationType o) {
    RegistrationThread* r = new RegistrationThread(this, ref_img, tar_img, t, s, o);
    connect(r, SIGNAL(transformedImageReady(cv::Mat*)), result_window, SLOT(updateTransformedImage(cv::Mat*)));
    r->start();
}
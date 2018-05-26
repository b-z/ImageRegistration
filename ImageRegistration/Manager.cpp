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
    //r_thread->exit(0);
    //delete r_thread;
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
    r_thread = new RegistrationThread(this, ref_img, tar_img, t, s, o);
    connect(r_thread, SIGNAL(transformedImageReady(cv::Mat*)), result_window, SLOT(updateTransformedImage(cv::Mat*)));
    connect(r_thread, SIGNAL(newDataPoint(int, double, double)), result_window, SLOT(addDataPoint(int, double, double)));
    r_thread->start();
}
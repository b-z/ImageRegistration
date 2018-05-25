#include "stdafx.h"
#include "RegistrationThread.h"

RegistrationThread::RegistrationThread(QObject *parent, cv::Mat ref, cv::Mat tar, Registration::TransformType t, Registration::SimilarityType s, Registration::OptimizationType o)
    : QThread(parent)
{
    r = new Registration(this, ref, tar, t, s, o);
    p_img = NULL;
}

RegistrationThread::~RegistrationThread()
{

}

void RegistrationThread::run() {
    r->runRegistration();
}

void RegistrationThread::showTransformedImage(cv::Mat* img) {
    if (!img->cols) {
        return;
    }
    emit transformedImageReady(img);
}

void RegistrationThread::addDataPoint(int iter, double loss, double min_loss) {
    emit newDataPoint(iter, loss, min_loss);
}

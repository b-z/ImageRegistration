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
    delete p_img;
    p_img = img;
    QImage qimg;
    if (img->channels() == 3) {
        qimg = QImage((const unsigned char *)(img->data), img->cols, img->rows, img->cols * img->channels(), QImage::Format_RGB888);
    } else if (img->channels() == 1) {
        qimg = QImage((const unsigned char *)(img->data), img->cols, img->rows, img->cols * img->channels(), QImage::Format_ARGB32);
    } else {
        qimg = QImage((const unsigned char *)(img->data), img->cols, img->rows, img->cols * img->channels(), QImage::Format_RGB888);
    }
    if (!img->cols) {
        return;
    }
    emit transformedImageReady(qimg);
}


#ifndef REGISTRATIONTHREAD_H
#define REGISTRATIONTHREAD_H

#include <QThread>
#include "Registration.h"

class RegistrationThread : public QThread
{
    Q_OBJECT

public:
    RegistrationThread(QObject *parent, cv::Mat ref, cv::Mat tar, Registration::TransformType t, Registration::SimilarityType s, Registration::OptimizationType o);
    ~RegistrationThread();
    void run() override;
    void showTransformedImage(cv::Mat* img);
public:
    Registration* r;
    cv::Mat* p_img;
signals:
    void transformedImageReady(QImage);

private:
    
};

#endif // REGISTRATIONTHREAD_H

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
    void addDataPoint(int iter, double loss, double min_loss);
public:
    Registration* r;
    cv::Mat* p_img;
signals:
    void transformedImageReady(cv::Mat*);
    void newDataPoint(int iter, double loss, double min_loss);
private:
    
};

#endif // REGISTRATIONTHREAD_H

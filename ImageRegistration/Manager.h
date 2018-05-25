#ifndef MANAGER_H
#define MANAGER_H
#define IMAGE_WIDTH 512
#include <QObject>
#include <opencv2\opencv.hpp>
#include "Registration.h"
//class Mat;
class ResultWindow;
class Manager : public QObject
{
    Q_OBJECT

public:
    Manager(QObject *parent, ResultWindow* r_window);
    ~Manager();

    cv::Mat loadImage();
    void runRegistration(Registration::TransformType t, Registration::SimilarityType s, Registration::OptimizationType o);

public slots:
    void loadReferenceImage();
    void loadTargetImage();
signals:
    void referenceImageReady();
    void targetImageReady();

public:

    cv::Mat ref_img;
    cv::Mat tar_img;
    ResultWindow* result_window;
private:
    
};

#endif // MANAGER_H

#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <opencv2\opencv.hpp>
//class Mat;
class Manager : public QObject
{
    Q_OBJECT

public:
    Manager(QObject *parent);
    ~Manager();

    cv::Mat loadImage();
public slots:
    void loadReferenceImage();
    void loadTargetImage();
    void runSimpleRegistration();
signals:
    void referenceImageReady();
    void targetImageReady();

public:
    cv::Mat ref_img;
    cv::Mat tar_img;

private:
    
};

#endif // MANAGER_H

#ifndef MANAGER_H
#define MANAGER_H
#define IMAGE_WIDTH 512
#include <QObject>
#include <opencv2\opencv.hpp>
//class Mat;
class ResultWindow;
class Manager : public QObject
{
    Q_OBJECT

public:
    Manager(QObject *parent, ResultWindow* r_window);
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
    ResultWindow* result_window;
private:
    
};

#endif // MANAGER_H

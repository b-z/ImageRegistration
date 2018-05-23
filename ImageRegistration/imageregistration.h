#ifndef IMAGEREGISTRATION_H
#define IMAGEREGISTRATION_H

#include <QtWidgets/QMainWindow>
#include "ui_imageregistration.h"
#include "Manager.h"

class ImageRegistration : public QMainWindow
{
    Q_OBJECT

public:
    ImageRegistration(QWidget *parent = 0);
    ~ImageRegistration();

public slots:
    void updateReferenceImage();
    void updateTargetImage();

public:
    Manager* manager;
private:
    Ui::ImageRegistrationClass ui;
};

#endif // IMAGEREGISTRATION_H

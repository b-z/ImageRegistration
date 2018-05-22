#ifndef IMAGEREGISTRATION_H
#define IMAGEREGISTRATION_H

#include <QtWidgets/QMainWindow>
#include "ui_imageregistration.h"

class ImageRegistration : public QMainWindow
{
    Q_OBJECT

public:
    ImageRegistration(QWidget *parent = 0);
    ~ImageRegistration();

private:
    Ui::ImageRegistrationClass ui;
};

#endif // IMAGEREGISTRATION_H

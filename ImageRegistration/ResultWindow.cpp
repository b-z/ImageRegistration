#include "stdafx.h"
#include "ResultWindow.h"
#include <iostream>
ResultWindow::ResultWindow(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
}

ResultWindow::~ResultWindow()
{

}


void ResultWindow::updateCombinedImage(QImage qimg) {
    show();
    ui.image->setPixmap(QPixmap::fromImage(qimg));
    ui.image->setFixedSize(IMAGE_WIDTH, qimg.height() * IMAGE_WIDTH / qimg.width());
    adjustSize();
}

#include "stdafx.h"
#include "ResultWindow.h"
#include <iostream>
ResultWindow::ResultWindow(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateCompareImage()));
    timer.setInterval(1000);
    timer.start();
    show_trans_img = false;
}

ResultWindow::~ResultWindow()
{

}

void ResultWindow::updateTargetImage(QImage qimg) {
    tar_qimg = qimg;
}

void ResultWindow::updateTransformedImage(QImage qimg) {
    show();
    trans_qimg = qimg;
    ui.image->setPixmap(QPixmap::fromImage(qimg));
    ui.image->setFixedSize(IMAGE_WIDTH, qimg.height() * IMAGE_WIDTH / qimg.width());
    adjustSize();
}

void ResultWindow::updateCompareImage() {
    if (tar_qimg.width() && trans_qimg.width()) {
        if (show_trans_img) {
            ui.image_cmp->setPixmap(QPixmap::fromImage(trans_qimg));
            ui.image_cmp->setFixedSize(IMAGE_WIDTH, trans_qimg.height() * IMAGE_WIDTH / trans_qimg.width());
        } else {
            ui.image_cmp->setPixmap(QPixmap::fromImage(tar_qimg));
            ui.image_cmp->setFixedSize(IMAGE_WIDTH, tar_qimg.height() * IMAGE_WIDTH / tar_qimg.width());
        }
        show_trans_img = !show_trans_img;
        adjustSize();
    }
}
#include "stdafx.h"
#include "ResultWindow.h"
#include <iostream>
ResultWindow::ResultWindow(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    p_img = NULL;
    chart = NULL;
    series1 = NULL;
    series2 = NULL;
    timer = NULL;
    chart_view = new QChartView();
    ui.verticalLayout_2->addWidget(chart_view);
    chart_view->setRenderHint(QPainter::Antialiasing);
    init();
}

ResultWindow::~ResultWindow()
{
    delete p_img;
}

void ResultWindow::init() {
    delete timer;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCompareImage()));
    timer->setInterval(1000);
    timer->start();
    show_trans_img = false;
    delete p_img;
    delete chart;
    delete series1;
    delete series2;
    chart = new QChart();
    series1 = new QLineSeries(chart);
    series2 = new QLineSeries(chart);
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->createDefaultAxes();
    chart_view->setChart(chart);
    point_count = 0;
    max_loss = 0;
}

void ResultWindow::updateTargetImage(QImage qimg) {
    tar_qimg = qimg;
}

void ResultWindow::updateTransformedImage(cv::Mat* img) {
    delete p_img;
    p_img = img;
    if (img->channels() == 3) {
        trans_qimg = QImage((const unsigned char *)(img->data), img->cols, img->rows, img->cols * img->channels(), QImage::Format_RGB888);
    } else if (img->channels() == 1) {
        trans_qimg = QImage((const unsigned char *)(img->data), img->cols, img->rows, img->cols * img->channels(), QImage::Format_ARGB32);
    } else {
        trans_qimg = QImage((const unsigned char *)(img->data), img->cols, img->rows, img->cols * img->channels(), QImage::Format_RGB888);
    }
    ui.image->setPixmap(QPixmap::fromImage(trans_qimg));
    ui.image->setFixedSize(IMAGE_WIDTH, trans_qimg.height() * IMAGE_WIDTH / trans_qimg.width());
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

void ResultWindow::addDataPoint(int iter, double loss, double min_loss) {
    series1->append(QPointF(iter, loss));
    series2->append(QPointF(iter, min_loss));
    if (series1->count() > 100) {
        series1->removePoints(0, 1);
        series2->removePoints(0, 1);
    }
    max_loss = MAX(max_loss, loss);
    chart->axisX()->setRange(series1->at(0).x(), iter);
    chart->axisY()->setRange(0, max_loss);
}
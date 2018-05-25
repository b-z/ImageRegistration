#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QDialog>
#include <QTimer>
#include "ui_ResultWindow.h"
#include "Manager.h"
#include <queue>
#include <QtCharts>

class ResultWindow : public QDialog
{
    Q_OBJECT

public:
    ResultWindow(QWidget *parent = 0);
    ~ResultWindow();
    void init();
public slots:
    void updateTransformedImage(cv::Mat* img);
    void updateTargetImage(QImage qimg);
    void updateCompareImage();
    void addDataPoint(int iter, double loss, double min_loss);

public:
    cv::Mat* p_img;
    QImage trans_qimg;
    QImage tar_qimg;
    QTimer* timer;
    bool show_trans_img;

    // chart:
    int point_count;
    double max_loss;
    QChart* chart;
    QChartView* chart_view;
    QLineSeries* series1;
    QLineSeries* series2;
private:
    Ui::ResultWindow ui;
};

#endif // RESULTWINDOW_H

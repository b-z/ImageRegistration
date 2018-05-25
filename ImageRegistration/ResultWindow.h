#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QDialog>
#include <QTimer>
#include "ui_ResultWindow.h"
#include "Manager.h"
#include <queue>

class ResultWindow : public QDialog
{
    Q_OBJECT

public:
    ResultWindow(QWidget *parent = 0);
    ~ResultWindow();
public slots:
    void updateTransformedImage(cv::Mat* img);
    void updateTargetImage(QImage qimg);
    void updateCompareImage();

public:
    cv::Mat* p_img;
    QImage trans_qimg;
    QImage tar_qimg;
    QTimer timer;
    bool show_trans_img;
private:
    Ui::ResultWindow ui;
};

#endif // RESULTWINDOW_H

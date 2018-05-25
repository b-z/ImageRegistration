#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QDialog>
#include <QTimer>
#include "ui_ResultWindow.h"
#include "Manager.h"


class ResultWindow : public QDialog
{
    Q_OBJECT

public:
    ResultWindow(QWidget *parent = 0);
    ~ResultWindow();
public slots:
    void updateTransformedImage(QImage qimg);
    void updateTargetImage(QImage qimg);
    void updateCompareImage();

public:
    QImage trans_qimg;
    QImage tar_qimg;
    QTimer timer;
    bool show_trans_img;
private:
    Ui::ResultWindow ui;
};

#endif // RESULTWINDOW_H

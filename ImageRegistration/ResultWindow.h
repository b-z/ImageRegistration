#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QDialog>
#include "ui_ResultWindow.h"
#include "Manager.h"

class ResultWindow : public QDialog
{
    Q_OBJECT

public:
    ResultWindow(QWidget *parent = 0);
    ~ResultWindow();

public slots:
    void updateCombinedImage(QImage qimg);

private:
    Ui::ResultWindow ui;
};

#endif // RESULTWINDOW_H

#include "stdafx.h"
#include "imageregistration.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageRegistration w;
    w.show();
    return a.exec();
}

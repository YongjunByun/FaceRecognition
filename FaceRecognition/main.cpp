#include "FaceRecognition.h"
#include "CameraWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CameraWidget mainwindow;
    mainwindow.show();
    return app.exec();
}

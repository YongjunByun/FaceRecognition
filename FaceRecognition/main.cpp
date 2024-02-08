#include "FaceRecognition.h"
#include "CameraWidget.h"
#include <QtWidgets/QApplication>
#include "LoadDnnModel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CameraWidget mainwindow;
    mainwindow.show();
    LoadDnnModel sample;
    sample.LoadOnnx();
    return app.exec();
}

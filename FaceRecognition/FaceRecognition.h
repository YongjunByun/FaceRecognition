#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FaceRecognition.h"

class FaceRecognition : public QMainWindow
{
    Q_OBJECT

public:
    FaceRecognition(QWidget *parent = nullptr);
    ~FaceRecognition();

private:
    Ui::FaceRecognitionClass ui;
};

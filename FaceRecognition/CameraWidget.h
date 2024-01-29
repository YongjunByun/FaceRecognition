#pragma once

#include <QWidget>
#include "ui_CameraWidget.h"
#include "QLabel.h"
#include "qdialog.h"
#include <QVBoxLayout>
#include <QTimer>
#include <opencv2/opencv.hpp>

#include "HaarCascade.h"
#include "Eigenfaces.h"

using namespace std;

class CameraWidget : public QWidget
{
	Q_OBJECT

public:
	CameraWidget(QWidget *parent = nullptr);
	~CameraWidget();

private slots:
	void updateImage();
	void GetFaceImage();
	void on_pushButton_Start_clicked();
	void on_pushButton_Stop_clicked();
	void addTextToBrowser(const QString& text); // 텍스트를 추가하는 슬롯
	void on_pushButton_add_person_data_clicked();
	void ShowFacesPopup();
private:
	cv::VideoCapture cap;
	QTimer* image_update_timer; //이 타이머는 특정 간격으로 updateImage() 슬롯을 호출합니다.
	QTimer* Eigenface_timer; //이 타이머는 특정 간격으로 GetFaceImage() 슬롯을 호출합니다.
	int imageCount;
	vector<cv::Mat> faces;
private:
	Ui::CameraWidgetClass ui;
	HaarCascade m_HaarCascade;
	//Eigenfaces m_Eigenfaces;
};

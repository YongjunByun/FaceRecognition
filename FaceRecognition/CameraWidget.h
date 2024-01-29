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
	void addTextToBrowser(const QString& text); // �ؽ�Ʈ�� �߰��ϴ� ����
	void on_pushButton_add_person_data_clicked();
	void ShowFacesPopup();
private:
	cv::VideoCapture cap;
	QTimer* image_update_timer; //�� Ÿ�̸Ӵ� Ư�� �������� updateImage() ������ ȣ���մϴ�.
	QTimer* Eigenface_timer; //�� Ÿ�̸Ӵ� Ư�� �������� GetFaceImage() ������ ȣ���մϴ�.
	int imageCount;
	vector<cv::Mat> faces;
private:
	Ui::CameraWidgetClass ui;
	HaarCascade m_HaarCascade;
	//Eigenfaces m_Eigenfaces;
};

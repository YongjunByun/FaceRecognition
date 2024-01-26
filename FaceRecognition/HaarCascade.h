#pragma once
#include "iostream"
#include "string"
#include <qobject.h>
#include <opencv2/opencv.hpp>

using namespace std;

class HaarCascade : public QObject
{
	Q_OBJECT

public:
	HaarCascade();
	~HaarCascade();
	void Load();
	bool DrawHaarCascadeFace(cv::Mat& in);
	bool getHaarCascadeFace(cv::Mat& in, cv::Mat& out);
private:
	cv::CascadeClassifier face_cascade;
	
	
signals:
	void textToAdd(const QString& text); // QTextBrowser�� �߰��� �ؽ�Ʈ�� �����ϴ� �ñ׳�
};


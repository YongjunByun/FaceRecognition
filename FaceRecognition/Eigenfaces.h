#pragma once
#include <opencv2/opencv.hpp>

class Eigenfaces
{
public:
	Eigenfaces(int imageWidth, int imageHeight);
	~Eigenfaces();
	void computeEigenfaces();
	void saveEigenface();

private:
	int width;
	int height;
	cv::Mat dataMatrix;  // ��ó���� �̹��� ������ ���
	cv::Mat meanFace;    // ��� ��
	cv::Mat eigenVectors; // SVD�� ���� Eigenfaces
	cv::Mat eigenValues;  // SVD�� ���� Ư�̰�

	//void convertToVector(const cv::Mat& image, cv::Mat& vector);
	//void reconstructFace(const cv::Mat& eigenFace);
};

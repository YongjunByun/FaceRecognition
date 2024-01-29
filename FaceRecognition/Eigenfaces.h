#pragma once
#include <opencv2/opencv.hpp>
#include <Eigen/Dense>
class Eigenfaces
{
public:
	Eigenfaces(int imageWidth, int imageHeight);
	~Eigenfaces();
	static Eigen::MatrixXd computeEigenfaces(const std::vector<cv::Mat>& images, int numComponents);
	void saveEigenface();

private:
	int width;
	int height;
	cv::Mat dataMatrix;  // 전처리된 이미지 데이터 행렬
	cv::Mat meanFace;    // 평균 얼굴
	cv::Mat eigenVectors; // SVD로 계산된 Eigenfaces
	cv::Mat eigenValues;  // SVD로 계산된 특이값


	//void convertToVector(const cv::Mat& image, cv::Mat& vector);
	//void reconstructFace(const cv::Mat& eigenFace);
};


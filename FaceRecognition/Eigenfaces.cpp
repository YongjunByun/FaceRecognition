#include "Eigenfaces.h"

Eigenfaces::Eigenfaces(int imageWidth, int imageHeight) {

}
Eigenfaces::~Eigenfaces() {

}

Eigen::MatrixXd Eigenfaces::computeEigenfaces(const std::vector<cv::Mat>&images, int numComponents) {
    int numImages = images.size();
    int imageArea = images[0].rows * images[0].cols;

    // 모든 이미지를 벡터로 변환하여 행렬 생성
    Eigen::MatrixXd data(imageArea, numImages);
    for (int i = 0; i < numImages; ++i) {
        cv::Mat imgDouble;
        images[i].convertTo(imgDouble, CV_64F);
        Eigen::Map<Eigen::VectorXd> imgVec(imgDouble.ptr<double>(), imageArea);
        data.col(i) = imgVec.cast<double>();
    }

    // 평균 얼굴 계산
    Eigen::VectorXd meanFace = data.rowwise().mean();

    // 중심으로 이동
    data.colwise() -= meanFace;

    // 공분산 행렬
    Eigen::MatrixXd covariance = data * data.transpose() / double(numImages);

    // 고유값과 고유벡터 계산
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigenSolver(covariance);
    Eigen::MatrixXd eigenVectors = eigenSolver.eigenvectors().rightCols(numComponents);

    // 고유 얼굴 계산
    Eigen::MatrixXd eigenFaces = data.transpose() * eigenVectors;

    return eigenFaces;
}
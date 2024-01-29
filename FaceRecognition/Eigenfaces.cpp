#include "Eigenfaces.h"

Eigenfaces::Eigenfaces(int imageWidth, int imageHeight) {

}
Eigenfaces::~Eigenfaces() {

}

Eigen::MatrixXd Eigenfaces::computeEigenfaces(const std::vector<cv::Mat>&images, int numComponents) {
    int numImages = images.size();
    int imageArea = images[0].rows * images[0].cols;

    // ��� �̹����� ���ͷ� ��ȯ�Ͽ� ��� ����
    Eigen::MatrixXd data(imageArea, numImages);
    for (int i = 0; i < numImages; ++i) {
        cv::Mat imgDouble;
        images[i].convertTo(imgDouble, CV_64F);
        Eigen::Map<Eigen::VectorXd> imgVec(imgDouble.ptr<double>(), imageArea);
        data.col(i) = imgVec.cast<double>();
    }

    // ��� �� ���
    Eigen::VectorXd meanFace = data.rowwise().mean();

    // �߽����� �̵�
    data.colwise() -= meanFace;

    // ���л� ���
    Eigen::MatrixXd covariance = data * data.transpose() / double(numImages);

    // �������� �������� ���
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigenSolver(covariance);
    Eigen::MatrixXd eigenVectors = eigenSolver.eigenvectors().rightCols(numComponents);

    // ���� �� ���
    Eigen::MatrixXd eigenFaces = data.transpose() * eigenVectors;

    return eigenFaces;
}
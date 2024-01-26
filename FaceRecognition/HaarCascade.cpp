#include "HaarCascade.h"

HaarCascade::HaarCascade()
{

}
HaarCascade::~HaarCascade()
{

}
void HaarCascade::Load()
{
    // OpenCV Haar Cascade �� ����� �ε��մϴ�
    if (!face_cascade.load("D:\\opencv_libs_4.8.1\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml")) {
        emit textToAdd("Haar Cascade ������ �ε��� �� �����ϴ�.\n");
    }
}
bool HaarCascade::DrawHaarCascadeFace(cv::Mat &in)
{
    cv::Mat gray;
    cvtColor(in, gray, cv::COLOR_BGR2GRAY); // ������� ��ȯ
    cv::equalizeHist(gray, gray); // ������׷� ��Ȱȭ

    // �� ����
    vector<cv::Rect> faces;
    face_cascade.detectMultiScale(gray, faces);

    for (size_t i = 0; i < faces.size(); i++) {
        // �� �ֺ��� �簢�� �׸���
        cv::rectangle(in, faces[i], cv::Scalar(255, 0, 0));
        return true;
    }
    return false;
}
bool HaarCascade::getHaarCascadeFace(cv::Mat& in, cv::Mat& out)
{
    cv::Mat gray;
    cvtColor(in, gray, cv::COLOR_BGR2GRAY); // ������� ��ȯ
    cv::equalizeHist(gray, gray); // ������׷� ��Ȱȭ

    // �� ����
    vector<cv::Rect> faces;
    face_cascade.detectMultiScale(gray, faces);

    for (size_t i = 0; i < faces.size(); i++) {
        // �� �ֺ��� �簢�� �׸���
        cv::rectangle(in, faces[i], cv::Scalar(255, 0, 0));

        // �� �κ� ũ��
        out = gray(faces[i]);

        // ũ�ӵ� �� �̹����� ���ϴ� 100x100ũ��� ����
        cv::resize(out, out, cv::Size(100, 100));
        return true;
    }
    return false;
}
#include "HaarCascade.h"

HaarCascade::HaarCascade()
{

}
HaarCascade::~HaarCascade()
{

}
void HaarCascade::Load()
{
    // OpenCV Haar Cascade 얼굴 검출기 로드합니다
    if (!face_cascade.load("D:\\opencv_libs_4.8.1\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml")) {
        emit textToAdd("Haar Cascade 파일을 로드할 수 없습니다.\n");
    }
}
bool HaarCascade::DrawHaarCascadeFace(cv::Mat &in)
{
    cv::Mat gray;
    cvtColor(in, gray, cv::COLOR_BGR2GRAY); // 흑백으로 변환
    cv::equalizeHist(gray, gray); // 히스토그램 평활화

    // 얼굴 검출
    vector<cv::Rect> faces;
    face_cascade.detectMultiScale(gray, faces);

    for (size_t i = 0; i < faces.size(); i++) {
        // 얼굴 주변에 사각형 그리기
        cv::rectangle(in, faces[i], cv::Scalar(255, 0, 0));
        return true;
    }
    return false;
}
bool HaarCascade::getHaarCascadeFace(cv::Mat& in, cv::Mat& out)
{
    cv::Mat gray;
    cvtColor(in, gray, cv::COLOR_BGR2GRAY); // 흑백으로 변환
    cv::equalizeHist(gray, gray); // 히스토그램 평활화

    // 얼굴 검출
    vector<cv::Rect> faces;
    face_cascade.detectMultiScale(gray, faces);

    for (size_t i = 0; i < faces.size(); i++) {
        // 얼굴 주변에 사각형 그리기
        cv::rectangle(in, faces[i], cv::Scalar(255, 0, 0));

        // 얼굴 부분 크롭
        out = gray(faces[i]);

        // 크롭된 얼굴 이미지를 원하는 100x100크기로 조정
        cv::resize(out, out, cv::Size(100, 100));
        return true;
    }
    return false;
}
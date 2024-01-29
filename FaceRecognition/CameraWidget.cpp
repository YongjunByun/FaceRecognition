#include "CameraWidget.h"

#define FACE_COUNT 64 // eigenface만들때 쓸 face이미지의 갯수

CameraWidget::CameraWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

    // OpenCV 카메라 초기화
    cap.open(0); // 0은 일반적으로 기본 카메라를 의미한다

    image_update_timer = new QTimer(this);
    Eigenface_timer = new QTimer(this);
    connect(&m_HaarCascade, &HaarCascade::textToAdd, this, &CameraWidget::addTextToBrowser);
    connect(image_update_timer, SIGNAL(timeout()), this, SLOT(updateImage()));
    connect(Eigenface_timer, SIGNAL(timeout()), this, SLOT(GetFaceImage()));

    m_HaarCascade.Load();
    imageCount = 0;
}

CameraWidget::~CameraWidget()
{}

void CameraWidget::updateImage() {
    cv::Mat frame;
    if (cap.read(frame)) { // 웹캠으로부터 이미지 캡처
        // OpenCV 이미지를 Qt QImage로 변환
        QImage qimg(frame.data, frame.cols, frame.rows, static_cast<int>(frame.step), QImage::Format_RGB888);
        ui.ImageLabel->setPixmap(QPixmap::fromImage(qimg.rgbSwapped())); // RGB를 BGR로 전환해야 할 수 있음
    }
}
void CameraWidget::GetFaceImage() {
    if (imageCount >= FACE_COUNT) {
        Eigenface_timer->stop();
        Eigenfaces::computeEigenfaces(faces, 20);
        ShowFacesPopup();
        return;
    }
    cv::Mat frame;
    cv::Mat face;
    if (cap.read(frame)) { // 웹캠으로부터 이미지 캡처
        bool success = m_HaarCascade.getHaarCascadeFace(frame, face);
        if (success == true) {
            imageCount++;
            faces.push_back(face.clone());
        }
        // OpenCV 이미지를 Qt QImage로 변환
        QImage qimg(frame.data, frame.cols, frame.rows, static_cast<int>(frame.step), QImage::Format_RGB888);
        ui.ImageLabel->setPixmap(QPixmap::fromImage(qimg.rgbSwapped())); // RGB를 BGR로 전환해야 할 수 있음
    }
}
void CameraWidget::on_pushButton_Start_clicked() {
    image_update_timer->start(30); // 약 30fps의 간격으로 설정
}
void CameraWidget::on_pushButton_Stop_clicked() {
    image_update_timer->stop(); // 약 30fps의 간격으로 설정
}
void CameraWidget::on_pushButton_add_person_data_clicked() {
    if (image_update_timer->isActive())
        image_update_timer->stop();
    imageCount = 0; // 이미지 카운터 초기화
    Eigenface_timer->start(30); // 30ms 간격으로 이미지 캡처 시작
}
void CameraWidget::addTextToBrowser(const QString& text) {
    ui.textBrowser->append(text);
}
void CameraWidget::ShowFacesPopup() {
    // 800x800 크기의 새로운 이미지 생성
    cv::Mat bigImage(800, 800, CV_8UC1, cv::Scalar(0, 0, 0));
    int x = 0, y = 0;

    for (const auto& face : faces) {
        face.copyTo(bigImage(cv::Rect(x * 100, y * 100, 100, 100)));
        if (++x >= 8) {
            x = 0;
            y++;
        }
    }
    faces.clear();
    // cv::Mat을 QImage로 변환
    QImage qBigImage(bigImage.data, bigImage.cols, bigImage.rows, static_cast<int>(bigImage.step), QImage::Format_Grayscale8);
    QPixmap pixmap = QPixmap::fromImage(qBigImage);

    // QPixmap을 QLabel에 설정하고 QDialog를 사용하여 보여줌
    QLabel* label = new QLabel;
    label->setPixmap(pixmap);
    label->setFixedSize(800, 800);

    QDialog* dialog = new QDialog(this);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(label);
    dialog->setLayout(layout);
    dialog->setWindowTitle("Face Images");
    dialog->exec(); //다이얼로그로 보여주기
}
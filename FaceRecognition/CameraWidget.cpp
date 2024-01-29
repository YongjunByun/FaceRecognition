#include "CameraWidget.h"

#define FACE_COUNT 64 // eigenface���鶧 �� face�̹����� ����

CameraWidget::CameraWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

    // OpenCV ī�޶� �ʱ�ȭ
    cap.open(0); // 0�� �Ϲ������� �⺻ ī�޶� �ǹ��Ѵ�

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
    if (cap.read(frame)) { // ��ķ���κ��� �̹��� ĸó
        // OpenCV �̹����� Qt QImage�� ��ȯ
        QImage qimg(frame.data, frame.cols, frame.rows, static_cast<int>(frame.step), QImage::Format_RGB888);
        ui.ImageLabel->setPixmap(QPixmap::fromImage(qimg.rgbSwapped())); // RGB�� BGR�� ��ȯ�ؾ� �� �� ����
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
    if (cap.read(frame)) { // ��ķ���κ��� �̹��� ĸó
        bool success = m_HaarCascade.getHaarCascadeFace(frame, face);
        if (success == true) {
            imageCount++;
            faces.push_back(face.clone());
        }
        // OpenCV �̹����� Qt QImage�� ��ȯ
        QImage qimg(frame.data, frame.cols, frame.rows, static_cast<int>(frame.step), QImage::Format_RGB888);
        ui.ImageLabel->setPixmap(QPixmap::fromImage(qimg.rgbSwapped())); // RGB�� BGR�� ��ȯ�ؾ� �� �� ����
    }
}
void CameraWidget::on_pushButton_Start_clicked() {
    image_update_timer->start(30); // �� 30fps�� �������� ����
}
void CameraWidget::on_pushButton_Stop_clicked() {
    image_update_timer->stop(); // �� 30fps�� �������� ����
}
void CameraWidget::on_pushButton_add_person_data_clicked() {
    if (image_update_timer->isActive())
        image_update_timer->stop();
    imageCount = 0; // �̹��� ī���� �ʱ�ȭ
    Eigenface_timer->start(30); // 30ms �������� �̹��� ĸó ����
}
void CameraWidget::addTextToBrowser(const QString& text) {
    ui.textBrowser->append(text);
}
void CameraWidget::ShowFacesPopup() {
    // 800x800 ũ���� ���ο� �̹��� ����
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
    // cv::Mat�� QImage�� ��ȯ
    QImage qBigImage(bigImage.data, bigImage.cols, bigImage.rows, static_cast<int>(bigImage.step), QImage::Format_Grayscale8);
    QPixmap pixmap = QPixmap::fromImage(qBigImage);

    // QPixmap�� QLabel�� �����ϰ� QDialog�� ����Ͽ� ������
    QLabel* label = new QLabel;
    label->setPixmap(pixmap);
    label->setFixedSize(800, 800);

    QDialog* dialog = new QDialog(this);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(label);
    dialog->setLayout(layout);
    dialog->setWindowTitle("Face Images");
    dialog->exec(); //���̾�α׷� �����ֱ�
}
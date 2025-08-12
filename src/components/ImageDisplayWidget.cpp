// src/components/ImageDisplayWidget.cpp
#include "ImageDisplayWidget.h"

ImageDisplayWidget::ImageDisplayWidget(QWidget *parent)
    : QWidget(parent), zoomFactor(1.0), minZoomFactor(0.1), maxZoomFactor(2.0)
{
    setupUI();

    //测试图片显示
    loadAndDisplayImage(".\\..\\..\\res\\TestImage-Chan.png");
}

void ImageDisplayWidget::setupUI()
{
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    scrollArea->setWidget(imageLabel);

    loadButton = new QPushButton("Load", this);
    connect(loadButton, &QPushButton::clicked, this, [this]() {
        QString filePath = QFileDialog::getOpenFileName(this, "Open Image", "", "Image Files (*.png *.jpg *.bmp)");
        if (!filePath.isEmpty()) {
            loadAndDisplayImage(filePath);
        }
    });

    grayscaleButton = new QPushButton("Grayscale", this);
    connect(grayscaleButton, &QPushButton::clicked, this, [this]() {
        convertToGrayscale();
    });

    zoomInButton = new QPushButton("+", this);
    zoomInButton->setFixedSize(30, 30);
    connect(zoomInButton, &QPushButton::clicked, this, [this]() {
        zoomIn();
    });

    zoomOutButton = new QPushButton("-", this);
    zoomOutButton->setFixedSize(30, 30);
    connect(zoomOutButton, &QPushButton::clicked, this, [this]() {
        zoomOut();
    });

    zoomSlider = new QSlider(Qt::Horizontal, this);
    zoomSlider->setRange(10, 200); // 设置范围
    zoomSlider->setValue(100); // 初始值为100，对应1.0缩放比例
    connect(zoomSlider, &QSlider::valueChanged, this, &ImageDisplayWidget::onZoomSliderValueChanged);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(zoomOutButton);
    bottomLayout->addWidget(zoomSlider);
    bottomLayout->addWidget(zoomInButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(bottomLayout);
    mainLayout->addWidget(loadButton);
    mainLayout->addWidget(grayscaleButton);

    setLayout(mainLayout);
}

void ImageDisplayWidget::displayPixmap()
{
    if (!currentPixmap.isNull())
    {
        QPixmap scaledPixmap = currentPixmap.scaled(currentPixmap.size() * zoomFactor, Qt::KeepAspectRatio);
        imageLabel->setPixmap(scaledPixmap);
        imageLabel->adjustSize();
    }
}

void ImageDisplayWidget::loadAndDisplayImage(const QString &filePath)
{
    originalImage = cv::imread(filePath.toStdString());
    if (!originalImage.empty())
    {
        cvtColor(originalImage, originalImage, cv::COLOR_BGR2RGB);
        QImage qImage(originalImage.data, originalImage.cols, originalImage.rows, originalImage.step, QImage::Format_RGB888);
        currentPixmap = QPixmap::fromImage(qImage);
        displayPixmap();
    }
}

void ImageDisplayWidget::zoomIn()
{
    zoomFactor *= 1.1;
    if (zoomFactor > maxZoomFactor) {
        zoomFactor = maxZoomFactor;
    }
    zoomSlider->setValue(static_cast<int>(zoomFactor * 100));
    displayPixmap();
}

void ImageDisplayWidget::zoomOut()
{
    zoomFactor /= 1.1;
    if (zoomFactor < minZoomFactor) {
        zoomFactor = minZoomFactor;
    }
    zoomSlider->setValue(static_cast<int>(zoomFactor * 100));
    displayPixmap();
}

void ImageDisplayWidget::onZoomSliderValueChanged(int value)
{
    zoomFactor = value / 100.0;
    if (zoomFactor < minZoomFactor) {
        zoomFactor = minZoomFactor;
    } else if (zoomFactor > maxZoomFactor) {
        zoomFactor = maxZoomFactor;
    }
    displayPixmap();
}

void ImageDisplayWidget::convertToGrayscale()
{
    if (!originalImage.empty())
    {
        cv::cvtColor(originalImage, grayscaleImage, cv::COLOR_RGB2GRAY);
        QImage qImage(grayscaleImage.data, grayscaleImage.cols, grayscaleImage.rows, grayscaleImage.step, QImage::Format_Grayscale8);
        currentPixmap = QPixmap::fromImage(qImage);
        displayPixmap();
    }
}
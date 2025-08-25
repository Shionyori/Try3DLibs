// src/components/ImageDisplayWidget.cpp
#include "ImageDisplayWidget.h"
#include <QMessageBox>

ImageDisplayWidget::ImageDisplayWidget(QWidget *parent, ElementListDock* elementListDock)
    : QWidget(parent), zoomFactor(1.0), minZoomFactor(0.1), maxZoomFactor(2.0), elementListDock(elementListDock)
{
    setupUI();
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
    detectShapesButton = new QPushButton("Detect Shapes", this); // 新增按钮
    connect(detectShapesButton, &QPushButton::clicked, this, [this]() {
        detectShapes();
    });

    detectCirclesButton = new QPushButton("Detect Circles", this);
    connect(detectCirclesButton, &QPushButton::clicked, this, [this]() {
        detectCircles();
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

    QHBoxLayout *zoomButtonLayout = new QHBoxLayout();
    zoomButtonLayout->addWidget(zoomOutButton);
    zoomButtonLayout->addWidget(zoomSlider);
    zoomButtonLayout->addWidget(zoomInButton);

    QHBoxLayout *operateButtonLayout = new QHBoxLayout();
    operateButtonLayout->addWidget(grayscaleButton);
    operateButtonLayout->addWidget(detectShapesButton);
    operateButtonLayout->addWidget(detectCirclesButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(zoomButtonLayout);
    mainLayout->addWidget(loadButton);
    mainLayout->addLayout(operateButtonLayout);

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

void ImageDisplayWidget::detectShapes()
{
    if (originalImage.empty()) {
        QMessageBox::warning(this, "Warning", "No image loaded!");
        return;
    }
    // 图像预处理
    cv::Mat grayImage;
    cv::cvtColor(originalImage, grayImage, cv::COLOR_BGR2GRAY); // 转为灰度图，便于边缘检测
    cv::Mat blurredImage;
    cv::GaussianBlur(grayImage, blurredImage, cv::Size(5, 5), 0); //  高斯模糊，降噪，提高边缘检测准确性
    cv::Mat edgedImage;
    cv::Canny(blurredImage, edgedImage, 50, 150); // Canny算法（边缘检测）

    // 轮廓检测
    std::vector<std::vector<cv::Point>> contours; // 点集
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(edgedImage, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE); // 只检测最外层

    cv::Mat resultImage = originalImage.clone();
    for (const auto& contour : contours) {
        // 形状识别
        double epsilon = 0.02 * cv::arcLength(contour, true);
        std::vector<cv::Point> approx;
        cv::approxPolyDP(contour, approx, epsilon, true);
        // 绘制轮廓并标记形状名称
        if (approx.size() == 3) {
            cv::drawContours(resultImage, std::vector<std::vector<cv::Point>>{approx}, -1, cv::Scalar(0, 255, 0), 2);
            cv::putText(resultImage, "Triangle", cv::Point(approx[0].x, approx[0].y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2);
        } else if (approx.size() == 4) {
            cv::drawContours(resultImage, std::vector<std::vector<cv::Point>>{approx}, -1, cv::Scalar(0, 0, 255), 2);
            cv::putText(resultImage, "Rectangle", cv::Point(approx[0].x, approx[0].y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 2);
        } else if (approx.size() > 4) {
            cv::drawContours(resultImage, std::vector<std::vector<cv::Point>>{approx}, -1, cv::Scalar(255, 0, 0), 2);
            cv::putText(resultImage, "Circle", cv::Point(approx[0].x, approx[0].y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 0, 0), 2);
        }
    }
    // 显示结果
    QImage qImage(resultImage.data, resultImage.cols, resultImage.rows, resultImage.step, QImage::Format_BGR888);
    currentPixmap = QPixmap::fromImage(qImage);
    displayPixmap();
}

void ImageDisplayWidget::detectCircles()
{
    if (originalImage.empty()) {
        QMessageBox::warning(this, "Warning", "No image loaded!");
        return;
    }

    cv::Mat grayImage;
    cv::cvtColor(originalImage, grayImage, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(grayImage, grayImage, cv::Size(9, 9), 2, 2);

    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(grayImage, circles, cv::HOUGH_GRADIENT, 1, grayImage.rows / 8, 200, 100);

    cv::Mat resultImage = originalImage.clone();
    for (size_t i = 0; i < circles.size(); i++) {
        cv::Vec3i c = circles[i];
        cv::Point center = cv::Point(c[0], c[1]);
        int radius = c[2];

        // Draw the circle center
        cv::circle(resultImage, center, 3, cv::Scalar(0, 100, 100), cv::FILLED, cv::LINE_AA);
        // Draw the circle outline
        cv::circle(resultImage, center, radius, cv::Scalar(255, 0, 255), 3, cv::LINE_AA);

        // Add circle to element list
        QString circleName = QString("Circle %1: Center (%2, %3), Radius %4")
                             .arg(i + 1).arg(c[0]).arg(c[1]).arg(c[2]);
        elementListDock->addCircleElement(circleName); // 直接使用成员变量
    }

    QImage qImage(resultImage.data, resultImage.cols, resultImage.rows, resultImage.step, QImage::Format_BGR888);
    currentPixmap = QPixmap::fromImage(qImage);
    displayPixmap();
}

void ImageDisplayWidget::setCircleDetectionMode(bool enabled)
{
    circleDetectionMode = enabled;
    if (enabled) {
        setCursor(Qt::CrossCursor);
        QMessageBox::information(this, "Circle Detection", "Click on the image to detect circles near that point.");
    } else {
        setCursor(Qt::ArrowCursor);
    }
}

void ImageDisplayWidget::mousePressEvent(QMouseEvent *event)
{
    if (circleDetectionMode && event->button() == Qt::LeftButton) {
        // 获取点击位置在图像上的坐标（考虑缩放和滚动）
        QPoint imagePos = event->pos();
        QPoint scrollPos = scrollArea->widget()->mapFromParent(imagePos);
        
        // 调整坐标以考虑缩放
        QPoint adjustedPos(
            static_cast<int>(scrollPos.x() / zoomFactor),
            static_cast<int>(scrollPos.y() / zoomFactor)
        );
        
        detectCirclesNearPoint(adjustedPos);
    } else {
        QWidget::mousePressEvent(event);
    }
}

void ImageDisplayWidget::detectCirclesNearPoint(const QPoint &point)
{
    if (originalImage.empty()) {
        QMessageBox::warning(this, "Warning", "No image loaded!");
        return;
    }

    // 定义检测区域（以点击点为中心的正方形区域）
    int regionSize = 200; // 区域大小
    int x = std::max(0, point.x() - regionSize/2);
    int y = std::max(0, point.y() - regionSize/2);
    int width = std::min(regionSize, originalImage.cols - x);
    int height = std::min(regionSize, originalImage.rows - y);
    
    if (width <= 0 || height <= 0) return;
    
    // 提取感兴趣区域
    cv::Mat roi = originalImage(cv::Rect(x, y, width, height));
    
    // 转换为灰度图
    cv::Mat grayRoi;
    cv::cvtColor(roi, grayRoi, cv::COLOR_BGR2GRAY);
    
    // 高斯模糊
    cv::GaussianBlur(grayRoi, grayRoi, cv::Size(9, 9), 2, 2);
    
    // 霍夫圆检测
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(grayRoi, circles, cv::HOUGH_GRADIENT, 1, 
                    grayRoi.rows/8, 200, 100, 0, 0);
    
    if (circles.empty()) {
        QMessageBox::information(this, "No Circles", "No circles detected near the clicked point.");
        return;
    }
    
    // 找到最接近点击点的圆
    int closestCircleIdx = 0;
    double minDistance = std::numeric_limits<double>::max();
    
    for (size_t i = 0; i < circles.size(); i++) {
        cv::Vec3f c = circles[i];
        double circleX = c[0] + x;
        double circleY = c[1] + y;
        double distance = std::sqrt(std::pow(circleX - point.x(), 2) + 
                                   std::pow(circleY - point.y(), 2));
        
        if (distance < minDistance) {
            minDistance = distance;
            closestCircleIdx = i;
        }
    }
    
    cv::Vec3f c = circles[closestCircleIdx];
    double centerX = c[0] + x;
    double centerY = c[1] + y;
    double radius = c[2];
    
    // 在原始图像上绘制狙击镜标识
    cv::Mat resultImage = originalImage.clone();
    drawSniperScope(resultImage, cv::Point(centerX, centerY), radius);
    
    // 显示结果图像
    QImage qImage(resultImage.data, resultImage.cols, resultImage.rows, resultImage.step, QImage::Format_BGR888);
    currentPixmap = QPixmap::fromImage(qImage);
    displayPixmap();
    
    // 添加到元素列表
    QString circleName = QString("Circle %1: Center (%2, %3), Radius %4")
                         .arg(elementListDock->getTreeWidget()->topLevelItemCount() + 1)
                         .arg(centerX).arg(centerY).arg(radius);
    elementListDock->addCircleElement(circleName, true);
    
    // 发出信号通知VTK显示圆形
    emit circleDetected(circleName, centerX, centerY, radius);
    
    // 退出检测模式
    setCircleDetectionMode(false);
}

void ImageDisplayWidget::drawSniperScope(cv::Mat &image, const cv::Point &center, int radius)
{
    // 绘制外圆
    cv::circle(image, center, radius, cv::Scalar(0, 255, 0), 2);
    
    // 绘制十字准线
    int lineLength = radius + 20;
    cv::line(image, 
             cv::Point(center.x - lineLength, center.y),
             cv::Point(center.x + lineLength, center.y),
             cv::Scalar(0, 255, 0), 2);
    cv::line(image, 
             cv::Point(center.x, center.y - lineLength),
             cv::Point(center.x, center.y + lineLength),
             cv::Scalar(0, 255, 0), 2);
    
    // 绘制内圆
    cv::circle(image, center, 5, cv::Scalar(0, 0, 255), 2);
    
    // 添加文本标注
    std::string text = "R: " + std::to_string(radius);
    cv::putText(image, text, 
                cv::Point(center.x + radius + 5, center.y),
                cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);
}
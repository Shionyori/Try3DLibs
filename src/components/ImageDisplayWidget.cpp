// src/components/ImageDisplayWidget.cpp
#include "ImageDisplayWidget.h"
#include <QBoxLayout>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPixmap>
#include <QScrollArea>
#include <QWheelEvent>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

ImageDisplayWidget::ImageDisplayWidget(QWidget *parent)
    : QWidget(parent)
{
    label = new QLabel("Image Display Area", this);
    label->setAlignment(Qt::AlignCenter);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(label);
    scrollArea->setWidgetResizable(true);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(scrollArea);
    setLayout(layout);

    // 将 QScrollArea 的 viewport 的滚轮事件传递给 ImageDisplayWidget
    scrollArea->viewport()->installEventFilter(this);
}

void ImageDisplayWidget::loadAndDisplayImage(const QString &filePath)
{
    cv::Mat img = cv::imread(filePath.toStdString());
    if (img.empty())
    {
        QMessageBox::critical(this, "Error", "无法加载图像！");
        return;
    }

    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    qImage = QImage(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);

    QPixmap pixmap = QPixmap::fromImage(qImage);
    label->setPixmap(pixmap);
}
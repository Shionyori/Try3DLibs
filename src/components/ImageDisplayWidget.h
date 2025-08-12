// src/components/ImageDisplayWidget.h
#ifndef IMAGEDISPLAYWIDGET_H
#define IMAGEDISPLAYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QScrollArea>
#include <QSlider>
#include <opencv2/opencv.hpp>

class ImageDisplayWidget : public QWidget
{
    Q_OBJECT

public:
    ImageDisplayWidget(QWidget *parent = nullptr);

    void loadAndDisplayImage(const QString &filePath);
    void convertToGrayscale();

private slots:
    void zoomIn();
    void zoomOut();
    void onZoomSliderValueChanged(int value);

private:
    QScrollArea *scrollArea;
    QLabel *imageLabel;
    QPushButton *loadButton;
    QPushButton *grayscaleButton;
    QPushButton *zoomInButton;
    QPushButton *zoomOutButton;
    QSlider *zoomSlider;
    cv::Mat originalImage;
    cv::Mat grayscaleImage;
    QPixmap currentPixmap;
    
    double zoomFactor;
    double minZoomFactor;
    double maxZoomFactor;

    void setupUI();
    void displayPixmap();
};

#endif // IMAGEDISPLAYWIDGET_H
// ImageDisplayWidget.h
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
#include <QMouseEvent>
#include <opencv2/opencv.hpp>

#include "ElementListDock.h"

class ImageDisplayWidget : public QWidget
{
    Q_OBJECT

public:
    ImageDisplayWidget(QWidget *parent = nullptr, ElementListDock* elementListDock = nullptr);

    void loadAndDisplayImage(const QString &filePath);
    void convertToGrayscale();
    void detectShapes();
    void detectCircles();
    void setCircleDetectionMode(bool enabled);

signals:
    void circleDetected(QString name, double centerX, double centerY, double radius);

private slots:
    void zoomIn();
    void zoomOut();
    void onZoomSliderValueChanged(int value);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QScrollArea *scrollArea;
    QLabel *imageLabel;
    QPushButton *loadButton;
    QPushButton *grayscaleButton;
    QPushButton *zoomInButton;
    QPushButton *zoomOutButton;
    QPushButton *detectShapesButton;
    QPushButton *detectCirclesButton;
    QSlider *zoomSlider;

    cv::Mat originalImage;
    cv::Mat grayscaleImage;
    QPixmap currentPixmap;

    double zoomFactor;
    double minZoomFactor;
    double maxZoomFactor;
    
    bool circleDetectionMode = false;
    QPoint lastClickPos;

    void setupUI();
    void displayPixmap();
    void detectCirclesNearPoint(const QPoint &point);
    void drawSniperScope(cv::Mat &image, const cv::Point &center, int radius);

    ElementListDock* elementListDock;
};

#endif // IMAGEDISPLAYWIDGET_H
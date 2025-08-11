// src/components/ImageDisplayWidget.h
#ifndef IMAGEDISPLAYWIDGET_H
#define IMAGEDISPLAYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <opencv2/opencv.hpp>

class ImageDisplayWidget : public QWidget
{
    Q_OBJECT

public:
    ImageDisplayWidget(QWidget *parent = nullptr);
    void loadAndDisplayImage(const QString &filePath);
    
private:
    QLabel *label;
    QImage qImage;
};

#endif // IMAGEDISPLAYWIDGET_H
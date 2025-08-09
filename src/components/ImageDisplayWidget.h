// src/components/ImageDisplayWidget.h
#ifndef IMAGEDISPLAYWIDGET_H
#define IMAGEDISPLAYWIDGET_H

#include <QWidget>
#include <QLabel>

class ImageDisplayWidget : public QWidget
{
    Q_OBJECT

public:
    ImageDisplayWidget(QWidget *parent = nullptr);
};

#endif // IMAGEDISPLAYWIDGET_H
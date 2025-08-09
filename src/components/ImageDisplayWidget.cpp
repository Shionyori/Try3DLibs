// src/components/ImageDisplayWidget.cpp
#include "ImageDisplayWidget.h"
#include <QBoxLayout>

ImageDisplayWidget::ImageDisplayWidget(QWidget *parent)
    : QWidget(parent)
{
    QLabel* label = new QLabel("Image Display Area", this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(label);
    setLayout(layout);
}
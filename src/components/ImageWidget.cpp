#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(400, 300);
    setStyleSheet("background-color: #e6e6ff; border: 1px solid #ccc; color: #333333");

    QLabel* label = new QLabel("图像", this);
    label->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0); 
    setLayout(layout);
}
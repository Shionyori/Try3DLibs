#include "propertywidget.h"

PropertyWidget::PropertyWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(150, 100);
    setStyleSheet("background-color: #e6ffff; border: 1px solid #ccc; color: #333333");

    QLabel* label = new QLabel("属性显示", this);
    label->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0); 
    setLayout(layout);
}
#include "elementlistwidget.h"

ElementListWidget::ElementListWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumWidth(150);
    setStyleSheet("background-color: #e6f7ff; border: 1px solid #ccc; color: #333333");

    QLabel* label = new QLabel("元素列表", this);
    label->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0); 
    setLayout(layout);
}
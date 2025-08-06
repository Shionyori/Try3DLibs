#include "operationwidget.h"

OperationWidget::OperationWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(150, 150);
    setStyleSheet("background-color: #ffffcc; border: 1px solid #ccc; color: #333333");

    QLabel* label = new QLabel("操作按钮", this);
    label->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0); 
    setLayout(layout);
}
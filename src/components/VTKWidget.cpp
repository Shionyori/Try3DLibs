#include "vtkwidget.h"

VTKWidget::VTKWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(400, 300);
    setStyleSheet("background-color: #ffe6f7; border: 1px solid #ccc; color: #333333");

    QLabel* label = new QLabel("VTK三维展示", this);
    label->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0); 
    setLayout(layout);
}
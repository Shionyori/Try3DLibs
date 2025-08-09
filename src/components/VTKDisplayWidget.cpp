// src/components/VTKDisplayWidget.cpp
#include "VTKDisplayWidget.h"
#include <QLabel>
#include <QBoxLayout>

VTKDisplayWidget::VTKDisplayWidget(QWidget *parent)
    : QWidget(parent)
{
    QLabel* label = new QLabel("VTK Display Area", this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(label);
    setLayout(layout);
}
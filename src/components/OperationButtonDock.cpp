// src/components/OperationButtonDock.cpp
#include "OperationButtonDock.h"

OperationButtonDock::OperationButtonDock(QWidget *parent)
    : QDockWidget("Operation Buttons", parent)
{
    QWidget* buttonWidget = new QWidget(this);
    QPushButton* button1 = new QPushButton("Button 1", buttonWidget);
    QPushButton* button2 = new QPushButton("Button 2", buttonWidget);
    QVBoxLayout* layout = new QVBoxLayout(buttonWidget);
    layout->addWidget(button1);
    layout->addWidget(button2);
    buttonWidget->setLayout(layout);

    setWidget(buttonWidget);
}
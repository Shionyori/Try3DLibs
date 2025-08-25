// OperationButtonDock.cpp
#include "OperationButtonDock.h"

OperationButtonDock::OperationButtonDock(QWidget *parent)
    : QDockWidget("Operation Buttons", parent)
{
    QWidget* buttonWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(buttonWidget);
    
    detectCirclesButton = new QPushButton("Detect Circles", buttonWidget);
    connect(detectCirclesButton, &QPushButton::clicked, this, [this]() {
        emit detectCirclesRequested();
    });
    
    layout->addWidget(detectCirclesButton);
    buttonWidget->setLayout(layout);

    setWidget(buttonWidget);
}
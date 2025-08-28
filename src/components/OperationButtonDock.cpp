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
    
    detectRectanglesButton = new QPushButton("Detect Rectangles", buttonWidget);
    connect(detectRectanglesButton, &QPushButton::clicked, this, [this]() {
        emit detectRectanglesRequested();
    });

    layout->addWidget(detectCirclesButton);
    layout->addWidget(detectRectanglesButton);

    buttonWidget->setLayout(layout);

    setWidget(buttonWidget);
}
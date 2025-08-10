// src/MainWindow.cpp
#include "MainWindow.h"
#include "components/ElementListDock.h"
#include "components/FileListDock.h"
#include "components/ImageDisplayWidget.h"
#include "components/VTKDisplayWidget.h"
#include "components/PropertyDisplayDock.h"
#include "components/OperationButtonDock.h"

#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry(150, 75, 1400, 900);
    createDocks();
    createCentralWidget();
}

MainWindow::~MainWindow() {}

void MainWindow::createDocks()
{
    // 创建ElementListDock
    elementListDock = new ElementListDock(this);
    addDockWidget(Qt::LeftDockWidgetArea, elementListDock);

    // 创建FileListDock
    fileListDock = new FileListDock(this);
    addDockWidget(Qt::LeftDockWidgetArea, fileListDock);

    // 创建PropertyDisplayDock
    propertyDisplayDock = new PropertyDisplayDock(this);
    addDockWidget(Qt::BottomDockWidgetArea, propertyDisplayDock);

    // 创建OperationButtonDock
    operationButtonDock = new OperationButtonDock(this);
    addDockWidget(Qt::BottomDockWidgetArea, operationButtonDock);

    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
}

void MainWindow::createCentralWidget()
{
    // 创建ImageDisplayWidget和VTKDisplayWidget
    imageDisplayWidget = new ImageDisplayWidget(this);
    vtkDisplayWidget = new VTKDisplayWidget(this);

    QSplitter* centralSplitter = new QSplitter(Qt::Horizontal, this);
    centralSplitter->addWidget(imageDisplayWidget);
    centralSplitter->addWidget(vtkDisplayWidget);

    // 设置初始大小
    centralSplitter->setSizes({500, 500});

    setCentralWidget(centralSplitter);
}
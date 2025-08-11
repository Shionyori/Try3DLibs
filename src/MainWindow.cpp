// src/MainWindow.cpp
#include "MainWindow.h"
#include "components/ElementListDock.h"
#include "components/FileListDock.h"
#include "components/ImageDisplayWidget.h"
#include "components/VTKDisplayWidget.h"
#include "components/PropertyDisplayDock.h"
#include "components/OperationButtonDock.h"

#include <QSplitter>
#include <QMenuBar>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry(150, 75, 1400, 900);
    setupMenu();
    setupToolBar();
    createDocks();
    createCentralWidget();

    // 测试图片加载
    imageDisplayWidget->loadAndDisplayImage(".\\..\\..\\res\\TestImage-Chan.png");
}

MainWindow::~MainWindow() {}

void MainWindow::setupMenu()
{
    QMenuBar* menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu* fileMenu = new QMenu("File", this);
    menuBar->addMenu(fileMenu);

    QAction* openAction = new QAction("Open", this);
    QAction* saveAction = new QAction("Save", this);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);

    menuBar->setStyleSheet(
        "QMenuBar { background-color: #333; color: white; }"
        "QMenu { background-color: #555; color: white; }"
        "QMenu::item:selected { background-color: #777; }"
    );
}

void MainWindow::setupToolBar()
{
    QToolBar* toolBar = new QToolBar("Toolbar", this);
    toolBar->setMovable(true);
    addToolBar(toolBar);

    toolBar->addAction(new QAction("ToolA", this));
    toolBar->addAction(new QAction("ToolB", this));

    toolBar->setStyleSheet(
        "QToolBar { background-color: #444; color: white; }"
        "QToolBar QToolButton { background-color: #666; color: white; }"
        "QToolBar QToolButton:hover { background-color: #888; }"
    );
}

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
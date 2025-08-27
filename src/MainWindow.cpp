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
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //设置窗口图标
    QIcon icon(":res/icons/app_icon.png");
    setWindowIcon(icon);
    // 加载QSS文件
    QFile styleFile(":res/styles/lightStyle.qss");
    styleFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleFile.readAll());
    setStyleSheet(styleSheet);

    setGeometry(150, 75, 1400, 900);
    setupMenu();
    setupToolBar();
    createDocks();
    createCentralWidget();
    setupConnection();
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
    
    openAction->setShortcut(QKeySequence("Ctrl+O"));
    saveAction->setShortcut(QKeySequence("Ctrl+S"));

    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
}

void MainWindow::setupToolBar()
{
    QToolBar* toolBar = new QToolBar("Toolbar", this);
    toolBar->setMovable(true);
    addToolBar(toolBar);

    toolBar->addAction(new QAction("ToolA", this));
    toolBar->addAction(new QAction("ToolB", this));
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
    imageDisplayWidget = new ImageDisplayWidget(this, elementListDock);
    vtkDisplayWidget = new VTKDisplayWidget(this);

    QSplitter* centralSplitter = new QSplitter(Qt::Horizontal, this);
    centralSplitter->addWidget(imageDisplayWidget);
    centralSplitter->addWidget(vtkDisplayWidget);

    // 设置初始大小
    centralSplitter->setSizes({500, 500});

    setCentralWidget(centralSplitter);
}

void MainWindow::setupConnection()
{
    // 连接点云文件可见性信号
    connect(fileListDock, &FileListDock::fileChecked, this, &MainWindow::handleFileChecked);

    // 连接操作按钮的信号
    connect(operationButtonDock, &OperationButtonDock::detectCirclesRequested, 
            this, [this]() {
                imageDisplayWidget->setCircleDetectionMode(true);
            });
    
    // 连接圆形检测信号
    connect(imageDisplayWidget, &ImageDisplayWidget::circleDetected, vtkDisplayWidget, &VTKDisplayWidget::displayCircle);

     // 连接元素可见性变化信号到属性更新
    connect(elementListDock, &ElementListDock::elementChecked, this, &MainWindow::handleElementChecked);

    // 连接元素列表的复选框状态变化
    connect(elementListDock, &ElementListDock::elementCheckedByName,
            this, [this](const QString& name, bool checked) {
                if (vtkDisplayWidget) {
                    vtkDisplayWidget->setCircleVisible(name, checked);
                }
            });

    // 连接圆形检测信号到属性更新
    connect(imageDisplayWidget, &ImageDisplayWidget::circleDetected, this, &MainWindow::handleCircleDetected);
}

void MainWindow::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Open Point Cloud",
        "",
        "Point Cloud Files (*.pcd *.ply *.obj *.stl)"
    );
    
    if (!filePath.isEmpty()) {
        // 添加到文件列表
        fileListDock->addFile(filePath);
    }
}

void MainWindow::handleFileChecked(const QString& filePath, bool checked)
{
    if (checked) {
        vtkDisplayWidget->displayPointCloud(filePath);
    } else {
        vtkDisplayWidget->removePointCloud(filePath);
    }
}

void MainWindow::handleElementChecked(int index, bool checked)
{
    QTreeWidgetItem* item = elementListDock->getTreeWidget()->topLevelItem(index);
    if (item) {
        QString elementName = item->text(0);
        // 发射按名称检查的信号
        emit elementListDock->elementCheckedByName(elementName, checked);
        
        // 原有的处理逻辑
        QRegularExpression re(R"(Circle \d+: Center \((\d+), (\d+)\), Radius (\d+))");
        QRegularExpressionMatch match = re.match(elementName);
        if (match.hasMatch()) {
            double centerX = match.captured(1).toDouble();
            double centerY = match.captured(2).toDouble();
            double radius = match.captured(3).toDouble();
            
            if (checked) {
                vtkDisplayWidget->displayCircle(elementName, centerX, centerY, radius);
            } else {
                vtkDisplayWidget->removeCircle(elementName);
            }
        }
    }
}

void MainWindow::handleCircleDetected(const QString& name, double centerX, double centerY, double radius)
{
    // 创建圆形属性
    ElementProperties circleProps(ElementType::Circle);
    circleProps.properties["Center X"] = centerX;
    circleProps.properties["Center Y"] = centerY;
    circleProps.properties["Radius"] = radius;
    
    // 更新属性显示
    propertyDisplayDock->updateElementProperties(name, circleProps);
}
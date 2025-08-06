#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QBoxLayout>

#include "components/ElementListWidget.h"
#include "components/ImageWidget.h"
#include "components/FileListWidget.h"
#include "components/OperationWidget.h"
#include "components/PropertyWidget.h"
#include "components/VTKWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupMenu();
    setupToolBar();
    setupWidgets();

    setMinimumSize(800, 600);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupMenu()
{
    QMenuBar* menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu* fileMenu = new QMenu("文件", this);
    menuBar->addMenu(fileMenu);

    QAction* openAction = new QAction("打开", this);
    QAction* saveAction = new QAction("保存", this);
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
    QToolBar* toolBar = new QToolBar("工具栏", this);
    toolBar->setMovable(true);
    addToolBar(toolBar);

    toolBar->addAction(new QAction("工具A", this));
    toolBar->addAction(new QAction("工具B", this));

    toolBar->setStyleSheet(
        "QToolBar { background-color: #444; color: white; }"
        "QToolBar QToolButton { background-color: #666; color: white; }"
        "QToolBar QToolButton:hover { background-color: #888; }"
    );
}

void MainWindow::setupWidgets()
{
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    QSplitter* mainSplitter = createMainSplitter();
    mainLayout->addWidget(mainSplitter);

    centralWidget->setLayout(mainLayout);
}

QSplitter* MainWindow::createMainSplitter()
{
    QSplitter* mainSplitter = new QSplitter(Qt::Horizontal);
    mainSplitter->setChildrenCollapsible(false);

    elementListWidget = new ElementListWidget();
    mainSplitter->addWidget(elementListWidget);

    QSplitter* rightSplitter = createRightSplitter();
    mainSplitter->addWidget(rightSplitter);

    return mainSplitter;
}

QSplitter* MainWindow::createRightSplitter()
{
    QSplitter* rightSplitter = new QSplitter(Qt::Vertical);
    rightSplitter->setChildrenCollapsible(false);

    QSplitter* topRightSplitter = createTopRightSplitter();
    rightSplitter->addWidget(topRightSplitter);

    QSplitter* bottomRightSplitter = createBottomRightSplitter();
    rightSplitter->addWidget(bottomRightSplitter);

    return rightSplitter;
}

QSplitter* MainWindow::createTopRightSplitter()
{
    QSplitter* topRightSplitter = new QSplitter(Qt::Horizontal);
    topRightSplitter->setChildrenCollapsible(false);

    imageWidget = new ImageWidget();
    topRightSplitter->addWidget(imageWidget);

    QSplitter* fileListAndOperationSplitter = new QSplitter(Qt::Vertical);
    fileListAndOperationSplitter->setChildrenCollapsible(false);

    fileListWidget = new FileListWidget();
    fileListAndOperationSplitter->addWidget(fileListWidget);

    operationWidget = new OperationWidget();
    fileListAndOperationSplitter->addWidget(operationWidget);

    topRightSplitter->addWidget(fileListAndOperationSplitter);

    return topRightSplitter;
}

QSplitter* MainWindow::createBottomRightSplitter()
{
    QSplitter* bottomRightSplitter = new QSplitter(Qt::Horizontal);
    bottomRightSplitter->setChildrenCollapsible(false);

    propertyWidget = new PropertyWidget();
    bottomRightSplitter->addWidget(propertyWidget);

    vtkWidget = new VTKWidget();
    bottomRightSplitter->addWidget(vtkWidget);

    return bottomRightSplitter;
}
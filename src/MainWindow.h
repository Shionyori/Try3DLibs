#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>

class ElementListWidget;
class ImageWidget;
class FileListWidget;
class OperationWidget;
class PropertyWidget;
class VTKWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupMenu();
    void setupToolBar();
    void setupWidgets();

    QSplitter* createMainSplitter();
    QSplitter* createRightSplitter();
    QSplitter* createTopRightSplitter();
    QSplitter* createBottomRightSplitter();

    ElementListWidget* elementListWidget;
    ImageWidget* imageWidget;
    FileListWidget* fileListWidget;
    OperationWidget* operationWidget;
    PropertyWidget* propertyWidget;
    VTKWidget* vtkWidget;
};

#endif // MAINWINDOW_H
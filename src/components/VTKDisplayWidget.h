// VTKDisplayWidget.h
#ifndef VTKDISPLAYWIDGET_H
#define VTKDISPLAYWIDGET_H

#include <QWidget>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkRegularPolygonSource.h> // 添加这行
#include <QMap>
#include <vtkAxesActor.h>  // 新增
#include <vtkOrientationMarkerWidget.h>  // 新增

class VTKDisplayWidget : public QWidget
{
    Q_OBJECT

public:
    VTKDisplayWidget(QWidget *parent = nullptr);

    void displayCone();
    
    void displayPointCloud(const QString& filePath);
    void removePointCloud(const QString& filePath);
    
public slots:
    void displayCircle(const QString& name, double centerX, double centerY, double radius);
    void removeCircle(const QString& circleName);
    void setCircleVisible(const QString& circleName, bool visible); // 新增方法

private:
    QVTKOpenGLNativeWidget* vtkWidget;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderer> renderer;
    QMap<QString, vtkSmartPointer<vtkActor>> pointCloudActors;  // 键值对存储actor
    QMap<QString, vtkSmartPointer<vtkActor>> circleActors;  // 键值对存储圆形actor

     // 新增：坐标轴缩略图相关
    vtkSmartPointer<vtkAxesActor> axesActor;
    vtkSmartPointer<vtkOrientationMarkerWidget> axesWidget;

    void setupCamera();
    void setupAxesWidget();  // 新增方法
};

#endif // VTKDISPLAYWIDGET_H
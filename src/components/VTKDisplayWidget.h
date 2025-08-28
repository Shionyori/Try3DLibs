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
    void displayRectangle(const QString& name, double centerX, double centerY, double width, double height, double angle);

    void removeCircle(const QString& circleName);
    void removeRectangle(const QString& rectangleName);

    void setCircleVisible(const QString& circleName, bool visible);
    void setRectangleVisible(const QString& rectangleName, bool visible);

private:
    QVTKOpenGLNativeWidget* vtkWidget;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderer> renderer;
    QMap<QString, vtkSmartPointer<vtkActor>> pointCloudActors;  // 键值对存储actor

    QMap<QString, vtkSmartPointer<vtkActor>> circleActors;
    QMap<QString, vtkSmartPointer<vtkActor>> rectangleActors;

    vtkSmartPointer<vtkAxesActor> axesActor;
    vtkSmartPointer<vtkOrientationMarkerWidget> axesWidget;

    void setupCamera();
    void setupAxesWidget();

    void createCircleActor(vtkSmartPointer<vtkActor>& actor, double centerX, double centerY, double radius);
    void createRectangleActor(vtkSmartPointer<vtkActor>& actor, double centerX, double centerY, double width, double height, double angle);
};

#endif // VTKDISPLAYWIDGET_H
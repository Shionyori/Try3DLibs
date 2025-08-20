// src/components/VTKDisplayWidget.cpp
#include "VTKDisplayWidget.h"

#include <QHBoxLayout>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>

#include <vtkConeSource.h>

#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>

VTKDisplayWidget::VTKDisplayWidget(QWidget* parent)
    : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);

    vtkWidget = new QVTKOpenGLNativeWidget(this);
    layout->addWidget(vtkWidget);

    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkWidget->setRenderWindow(renderWindow);

    renderWindow->AddRenderer(renderer);

    // 默认显示测试锥体
    displayCone();

    setupCamera();
}

void VTKDisplayWidget::displayCone()
{
    vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();
    cone->SetHeight(10.0);  
    cone->SetRadius(5.0);   
    cone->SetCenter(0, 0, 0);  
    cone->SetResolution(10);

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(cone->GetOutputPort());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    renderer->AddActor(actor);
    
    renderWindow->Render();
}

void VTKDisplayWidget::displayPointCloud(const QString& filePath)
{
     if (pointCloudActors.contains(filePath)) {
        removePointCloud(filePath);
    }

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    if (pcl::io::loadPCDFile<pcl::PointXYZ>(filePath.toStdString(), *cloud) == -1)
    {
        qDebug() << "The .pcd file not found \n";
        return;
    }
    qDebug() << "Found";

    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> vertices = vtkSmartPointer<vtkCellArray>::New();
    for (int i = 0; i < cloud->points.size(); i++)
    {
        points->InsertNextPoint(cloud->points[i].x, cloud->points[i].y, cloud->points[i].z);
        vertices->InsertNextCell(1);
        vertices->InsertCellPoint(i);
    }

    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData->SetPoints(points);
    polyData->SetVerts(vertices);

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polyData);

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetPointSize(2);
    actor->GetProperty()->SetColor(1.0, 1.0, 1.0);  // 设置点云为白色

    renderer->AddActor(actor);

    // 存储actor并添加到渲染器
    pointCloudActors[filePath] = actor;
    renderer->AddActor(actor);
    
    // 刷新渲染
    renderWindow->Render();
}

void VTKDisplayWidget::removePointCloud(const QString& filePath)
{
    if (pointCloudActors.contains(filePath)) {
        renderer->RemoveActor(pointCloudActors[filePath]);
        pointCloudActors.remove(filePath);
        renderWindow->Render(); 
    }
}

void VTKDisplayWidget::setupCamera()
{
    renderer->ResetCamera();  // 重置相机位置
    renderer->GetActiveCamera()->SetPosition(30, 30, 30);  // 将相机移远
    renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);  // 设置焦点位置
    renderer->GetActiveCamera()->SetViewUp(0, 1, 0);  // 设置视图方向
    renderer->SetBackground(0.2, 0.3, 0.4);  // 设置背景颜色
    renderWindow->Render();  // 渲染窗口
}

void VTKDisplayWidget::displayCircle(double centerX, double centerY, double radius)
{
    QString circleName = QString("Circle %1: Center (%2, %3), Radius %4")
                         .arg(circleActors.size() + 1).arg(centerX).arg(centerY).arg(radius);

    if (circleActors.contains(circleName)) {
        renderer->RemoveActor(circleActors[circleName]);
    }

    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetCenter(centerX, centerY, 0);
    sphereSource->SetRadius(radius);
    sphereSource->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(1.0, 1.0, 1.0); // 设置颜色为红色

    renderer->AddActor(actor);
    circleActors[circleName] = actor;
    renderWindow->Render();
}

void VTKDisplayWidget::removeCircle(const QString& circleName)
{
    if (circleActors.contains(circleName)) {
        renderer->RemoveActor(circleActors[circleName]);
        circleActors.remove(circleName);
        renderWindow->Render();
    }
}
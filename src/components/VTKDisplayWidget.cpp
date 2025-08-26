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
#include <QVector3D>

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

    setupCamera();
    setupAxesWidget();
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
    // 设置相机位置
    renderer->GetActiveCamera()->SetPosition(250, 250, 1500);  // 相机位于区域中心上方
    renderer->GetActiveCamera()->SetFocalPoint(250, 250, 0);   // 焦点位于区域中心
    renderer->GetActiveCamera()->SetViewUp(0, 1, 0);           // 设置视图向上方向
    renderer->SetBackground(1.0, 1.0, 1.0);

    renderer->ResetCamera();

    renderWindow->Render();
}

void VTKDisplayWidget::displayCircle(const QString& name, double centerX, double centerY, double radius)
{
    if (circleActors.contains(name)) {
        // 更新现有圆形
        removeCircle(name);
    }
    
    // 创建圆上的点集
    auto points = vtkSmartPointer<vtkPoints>::New();
    const int numPoints = 100; // 圆的点数，更多点数会更平滑
    
    // 法向量固定为Z轴方向 (0, 0, 1)
    QVector3D normalVec(0, 0, 1);
    
    // 创建一个与法向量正交的向量
    QVector3D v1(1, 0, 0);
    if (fabs(QVector3D::dotProduct(v1, normalVec)) > 0.99) {
        v1 = QVector3D(0, 1, 0);
    }
    QVector3D v2 = QVector3D::crossProduct(normalVec, v1).normalized();
    v1 = QVector3D::crossProduct(v2, normalVec).normalized();
    
    for (int i = 0; i < numPoints; ++i) {
        double theta = 2.0 * vtkMath::Pi() * static_cast<double>(i) / static_cast<double>(numPoints);
        double x = centerX + radius * (v1.x() * cos(theta) + v2.x() * sin(theta));
        double y = centerY + radius * (v1.y() * cos(theta) + v2.y() * sin(theta));
        double z = 0; // Z坐标设为0，因为我们是在XY平面上绘制
        points->InsertNextPoint(x, y, z);
    }
    
    // 创建一个线源来表示圆的线（多段线）
    auto lines = vtkSmartPointer<vtkCellArray>::New();
    vtkIdType pointIds[2];
    for (int i = 0; i < numPoints - 1; ++i) {
        pointIds[0] = i;
        pointIds[1] = i + 1;
        lines->InsertNextCell(2, pointIds);
    }
    // 闭环：将最后一个点与第一个点连接起来
    pointIds[0] = numPoints - 1;
    pointIds[1] = 0;
    lines->InsertNextCell(2, pointIds);
    
    // 创建PolyData并设置点和线
    auto polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData->SetPoints(points);
    polyData->SetLines(lines);
    
    // 创建映射器和actor
    auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polyData);
    
    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(0.0, 0.0, 0.0); // 黑色
    actor->GetProperty()->SetLineWidth(2.0); // 线宽
    
    renderer->AddActor(actor);
    circleActors[name] = actor;
    
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

void VTKDisplayWidget::setCircleVisible(const QString& circleName, bool visible)
{
    if (circleActors.contains(circleName)) {
        circleActors[circleName]->SetVisibility(visible ? 1 : 0);
        renderWindow->Render();
    }
}

void VTKDisplayWidget::setupAxesWidget()
{
    // 创建坐标轴actor
    axesActor = vtkSmartPointer<vtkAxesActor>::New();
    axesActor->SetShaftTypeToCylinder();
    axesActor->SetXAxisLabelText("X");
    axesActor->SetYAxisLabelText("Y");
    axesActor->SetZAxisLabelText("Z");
    axesActor->SetTotalLength(1.0, 1.0, 1.0);
    axesActor->SetCylinderRadius(0.5 * axesActor->GetCylinderRadius());
    axesActor->SetConeRadius(1.025 * axesActor->GetConeRadius());
    axesActor->SetSphereRadius(1.5 * axesActor->GetSphereRadius());
    
    // 创建方向标记widget
    axesWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    axesWidget->SetOutlineColor(0.9300, 0.5700, 0.1300);
    axesWidget->SetOrientationMarker(axesActor);
    axesWidget->SetInteractor(renderWindow->GetInteractor());
    axesWidget->SetViewport(0.0, 0.0, 0.2, 0.2);  // 设置在左下角
    axesWidget->SetEnabled(true);
    axesWidget->InteractiveOff();  // 设置为非交互式
}
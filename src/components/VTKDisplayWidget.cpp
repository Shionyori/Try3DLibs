// src/components/VTKDisplayWidget.cpp
#include "VTKDisplayWidget.h"

#include <QHBoxLayout>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>

VTKDisplayWidget::VTKDisplayWidget(QWidget* parent)
    : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);

    vtkWidget = new QVTKOpenGLNativeWidget(this);
    layout->addWidget(vtkWidget);

    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkWidget->setRenderWindow(renderWindow);

    vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(cone->GetOutputPort());
    
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    
    renderer->AddActor(actor);
    renderer->SetBackground(0.2, 0.3, 0.4);  // 设置背景色
    renderer->ResetCamera();  // 重置相机位置

    renderWindow->AddRenderer(renderer);  // 确保渲染器被添加到渲染窗口中
}
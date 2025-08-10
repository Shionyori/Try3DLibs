// src/components/VTKDisplayWidget.h
#ifndef VTKDISPLAYWIDGET_H
#define VTKDISPLAYWIDGET_H

#include <QWidget>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkSmartPointer.h>

class VTKDisplayWidget : public QWidget
{
    Q_OBJECT

public:
    VTKDisplayWidget(QWidget *parent = nullptr);
    
private:
    QVTKOpenGLNativeWidget* vtkWidget;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderer> renderer;
};

#endif // VTKDISPLAYWIDGET_H
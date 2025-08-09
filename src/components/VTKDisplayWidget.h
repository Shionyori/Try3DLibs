// src/components/VTKDisplayWidget.h
#ifndef VTKDISPLAYWIDGET_H
#define VTKDISPLAYWIDGET_H

#include <QWidget>

class VTKDisplayWidget : public QWidget
{
    Q_OBJECT

public:
    VTKDisplayWidget(QWidget *parent = nullptr);
};

#endif // VTKDISPLAYWIDGET_H
#ifndef VTKWIDGET_H
#define VTKWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class VTKWidget : public QWidget
{
    Q_OBJECT

public:
    VTKWidget(QWidget *parent = nullptr);
};

#endif // VTKWIDGET_H
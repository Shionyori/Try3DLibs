#ifndef PROPERTYWIDGET_H
#define PROPERTYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class PropertyWidget : public QWidget
{
    Q_OBJECT

public:
    PropertyWidget(QWidget *parent = nullptr);
};

#endif // PROPERTYWIDGET_H
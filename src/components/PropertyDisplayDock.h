// src/components/PropertyDisplayDock.h
#ifndef PROPERTYDISPLAYDOCK_H
#define PROPERTYDISPLAYDOCK_H

#include <QDockWidget>
#include <QTextEdit>

class PropertyDisplayDock : public QDockWidget
{
    Q_OBJECT

public:
    PropertyDisplayDock(QWidget *parent = nullptr);
};

#endif // PROPERTYDISPLAYDOCK_H
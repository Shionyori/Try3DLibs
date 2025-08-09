// src/components/ElementListDock.h
#ifndef ELEMENTLISTDOCK_H
#define ELEMENTLISTDOCK_H

#include <QDockWidget>
#include <QTreeWidget>

class ElementListDock : public QDockWidget
{
    Q_OBJECT

public:
    ElementListDock(QWidget *parent = nullptr);
};

#endif // ELEMENTLISTDOCK_H
// src/components/PropertyDisplayDock.cpp
#include "PropertyDisplayDock.h"

PropertyDisplayDock::PropertyDisplayDock(QWidget *parent)
    : QDockWidget("Property Display", parent)
{
    QTextEdit* textEdit = new QTextEdit(this);
    setWidget(textEdit);
}
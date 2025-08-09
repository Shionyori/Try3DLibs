// src/components/FileListDock.cpp
#include "FileListDock.h"

FileListDock::FileListDock(QWidget *parent)
    : QDockWidget("File List", parent)
{
    QListWidget* listWidget = new QListWidget(this);
    setWidget(listWidget);
}
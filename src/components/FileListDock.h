// src/components/FileListDock.h
#ifndef FILELISTDOCK_H
#define FILELISTDOCK_H

#include <QDockWidget>
#include <QListWidget>

class FileListDock : public QDockWidget
{
    Q_OBJECT

public:
    FileListDock(QWidget *parent = nullptr);
};

#endif // FILELISTDOCK_H
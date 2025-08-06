#ifndef FILELISTWIDGET_H
#define FILELISTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class FileListWidget : public QWidget
{
    Q_OBJECT

public:
    FileListWidget(QWidget *parent = nullptr);
};

#endif // FILELISTWIDGET_H
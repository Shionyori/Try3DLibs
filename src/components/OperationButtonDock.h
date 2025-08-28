// OperationButtonDock.h
#ifndef OPERATIONBUTTONDOCK_H
#define OPERATIONBUTTONDOCK_H

#include <QDockWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class OperationButtonDock : public QDockWidget
{
    Q_OBJECT

public:
    OperationButtonDock(QWidget *parent = nullptr);

signals:
    void detectCirclesRequested();
    void detectRectanglesRequested();

private:
    QPushButton* detectCirclesButton;
    QPushButton* detectRectanglesButton;
};

#endif // OPERATIONBUTTONDOCK_H
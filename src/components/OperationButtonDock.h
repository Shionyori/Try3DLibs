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
    
    QPushButton* getDetectCirclesButton() { return detectCirclesButton; }

signals:
    void detectCirclesRequested();

private:
    QPushButton* detectCirclesButton;
};

#endif // OPERATIONBUTTONDOCK_H
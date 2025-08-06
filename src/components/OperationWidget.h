#ifndef OPERATIONWIDGET_H
#define OPERATIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class OperationWidget : public QWidget
{
    Q_OBJECT

public:
    OperationWidget(QWidget *parent = nullptr);
};

#endif // OPERATIONWIDGET_H
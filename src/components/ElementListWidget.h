#ifndef ELEMENTLISTWIDGET_H
#define ELEMENTLISTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class ElementListWidget : public QWidget
{
    Q_OBJECT

public:
    ElementListWidget(QWidget *parent = nullptr);
};

#endif // ELEMENTLISTWIDGET_H
#ifndef ELEMENTLISTDOCK_H
#define ELEMENTLISTDOCK_H

#include <QDockWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QCheckBox>
#include <QVector>

class ElementListDock : public QDockWidget
{
    Q_OBJECT

public:
    ElementListDock(QWidget *parent = nullptr);
    QTreeWidget* getTreeWidget() {return treeWidget;}
    void addCircleElement(const QString& name, bool checked = false);
    void setElementChecked(int index, bool checked); // 新增方法
    
signals:
    void elementChecked(int index, bool checked);
    void elementCheckedByName(const QString& name, bool checked); // 新增信号

private:
    QTreeWidget* treeWidget;
};

#endif // ELEMENTLISTDOCK_H
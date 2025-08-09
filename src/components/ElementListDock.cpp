// src/components/ElementListDock.cpp
#include "ElementListDock.h"

ElementListDock::ElementListDock(QWidget *parent)
    : QDockWidget("Element List", parent)
{
    QTreeWidget* treeWidget = new QTreeWidget(this);
    setWidget(treeWidget);

     // 设置列数
    treeWidget->setColumnCount(1);
    treeWidget->setHeaderLabels(QStringList() << "Elements");

    // 添加顶级条目
    QTreeWidgetItem* topLevelItem1 = new QTreeWidgetItem(treeWidget);
    topLevelItem1->setText(0, "Top Level Item 1");

    QTreeWidgetItem* topLevelItem2 = new QTreeWidgetItem(treeWidget);
    topLevelItem2->setText(0, "Top Level Item 2");

    // 添加子条目
    QTreeWidgetItem* childItem1 = new QTreeWidgetItem();
    childItem1->setText(0, "Child Item 1");
    topLevelItem1->addChild(childItem1);

    QTreeWidgetItem* childItem2 = new QTreeWidgetItem();
    childItem2->setText(0, "Child Item 2");
    topLevelItem1->addChild(childItem2);

    QTreeWidgetItem* childItem3 = new QTreeWidgetItem();
    childItem3->setText(0, "Child Item 3");
    topLevelItem2->addChild(childItem3);

    // 展开顶级条目
    topLevelItem1->setExpanded(true);
    topLevelItem2->setExpanded(true);
}
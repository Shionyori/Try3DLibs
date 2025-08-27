// src/components/PropertyDisplayDock.cpp
#include "PropertyDisplayDock.h"
#include <QHeaderView>
#include <QVBoxLayout>

PropertyDisplayDock::PropertyDisplayDock(QWidget *parent)
    : QDockWidget("Property Display", parent)
{
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(2);
    tableWidget->setHorizontalHeaderLabels({"Property", "Value"});
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    // 隐藏垂直表头（行号列）
    tableWidget->verticalHeader()->setVisible(false);
    
    setWidget(tableWidget);
}

void PropertyDisplayDock::updateElementProperties(const QString& elementName, const ElementProperties& properties)
{
    // 更新内部映射
    elementPropertiesMap[elementName] = properties;
    
    // 刷新表格显示
    refreshTable();
}

void PropertyDisplayDock::removeElementProperties(const QString& elementName)
{
    if (elementPropertiesMap.contains(elementName)) {
        elementPropertiesMap.remove(elementName);
        // 刷新表格显示
        refreshTable();
    }
}

void PropertyDisplayDock::clearAllProperties()
{
    elementPropertiesMap.clear();
    refreshTable();
}

void PropertyDisplayDock::refreshTable()
{
    // 清空表格
    tableWidget->setRowCount(0);
    
    // 如果没有元素，显示空表格
    if (elementPropertiesMap.isEmpty()) {
        return;
    }
    
    // 重新填充表格
    int row = 0;
    for (const auto& element : elementPropertiesMap.keys()) {
        const ElementProperties& props = elementPropertiesMap[element];
        
        // 添加元素名称行
        tableWidget->insertRow(row);
        QTableWidgetItem* nameItem = new QTableWidgetItem("Element");
        nameItem->setBackground(QBrush(QColor(240, 240, 240)));
        nameItem->setFlags(nameItem->flags() ^ Qt::ItemIsEditable); // 设置为不可编辑
        tableWidget->setItem(row, 0, nameItem);
        
        QTableWidgetItem* valueItem = new QTableWidgetItem(element);
        valueItem->setBackground(QBrush(QColor(240, 240, 240)));
        valueItem->setFlags(valueItem->flags() ^ Qt::ItemIsEditable); // 设置为不可编辑
        tableWidget->setItem(row, 1, valueItem);
        row++;
        
        // 添加类型行
        tableWidget->insertRow(row);
        QTableWidgetItem* typeNameItem = new QTableWidgetItem("Type");
        typeNameItem->setFlags(typeNameItem->flags() ^ Qt::ItemIsEditable);
        tableWidget->setItem(row, 0, typeNameItem);
        
        QTableWidgetItem* typeValueItem = new QTableWidgetItem(getDisplayNameForType(props.type));
        typeValueItem->setFlags(typeValueItem->flags() ^ Qt::ItemIsEditable);
        tableWidget->setItem(row, 1, typeValueItem);
        row++;
        
        // 添加属性行
        QStringList propertyNames = getPropertyNamesForType(props.type);
        for (const QString& propName : propertyNames) {
            if (props.properties.contains(propName)) {
                tableWidget->insertRow(row);
                
                QTableWidgetItem* propNameItem = new QTableWidgetItem(propName);
                propNameItem->setFlags(propNameItem->flags() ^ Qt::ItemIsEditable);
                tableWidget->setItem(row, 0, propNameItem);
                
                QTableWidgetItem* propValueItem = new QTableWidgetItem(props.properties[propName].toString());
                propValueItem->setFlags(propValueItem->flags() ^ Qt::ItemIsEditable);
                tableWidget->setItem(row, 1, propValueItem);
                row++;
            }
        }
        
        // 添加空行作为分隔
        tableWidget->insertRow(row);
        row++;
    }
    
    // 调整列宽
    tableWidget->resizeColumnToContents(0);
}

QStringList PropertyDisplayDock::getPropertyNamesForType(ElementType type) const
{
    switch (type) {
        case ElementType::Circle:
            return {"Center X", "Center Y", "Radius"};
        default:
            return QStringList();
    }
}

QString PropertyDisplayDock::getDisplayNameForType(ElementType type) const
{
    switch (type) {
        case ElementType::Circle:
            return "Circle";
        default:
            return "Unknown";
    }
}
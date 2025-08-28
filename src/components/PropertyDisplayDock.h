// src/components/PropertyDisplayDock.h
#ifndef PROPERTYDISPLAYDOCK_H
#define PROPERTYDISPLAYDOCK_H

#include <QDockWidget>
#include <QTableWidget>
#include <QMap>
#include <QString>

// 元素类型枚举
enum class ElementType {
    Circle,
    Rectangle,
    // 未来可以添加其他类型
    Unknown
};

// 元素属性结构
struct ElementProperties {
    ElementType type;
    QMap<QString, QVariant> properties;
    
    ElementProperties() : type(ElementType::Unknown) {}
    ElementProperties(ElementType t) : type(t) {}
};

class PropertyDisplayDock : public QDockWidget
{
    Q_OBJECT

public:
    PropertyDisplayDock(QWidget *parent = nullptr);
    
    // 添加或更新元素属性
    void updateElementProperties(const QString& elementName, const ElementProperties& properties);
    
    // 移除元素属性
    void removeElementProperties(const QString& elementName);
    
    // 清空所有属性
    void clearAllProperties();

private:
    QTableWidget* tableWidget;
    QMap<QString, ElementProperties> elementPropertiesMap;
    
    // 刷新表格显示
    void refreshTable();
    
    // 根据元素类型获取属性名称列表
    QStringList getPropertyNamesForType(ElementType type) const;
    
    // 根据元素类型获取属性显示名称
    QString getDisplayNameForType(ElementType type) const;
};

#endif // PROPERTYDISPLAYDOCK_H
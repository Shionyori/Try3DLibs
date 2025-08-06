#include "filelistwidget.h"

FileListWidget::FileListWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(150, 150);
    setStyleSheet("background-color: #ffe6e6; border: 1px solid #ccc; color: #333333");

    QLabel* label = new QLabel("文件列表", this);
    label->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0); 
    setLayout(layout);
}
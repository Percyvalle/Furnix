#pragma once

#include <QLabel>
#include <QScrollArea>

class ComponentFactory
{
public:
    static QScrollArea* CreateScrollArea(QWidget* content);
    static QLabel* CreateLabel(const QString& text);
};
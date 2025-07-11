#pragma once

#include <QGraphicsProxyWidget>

class FurnacePartTooltip : public QGraphicsProxyWidget
{
public:
    explicit FurnacePartTooltip(QGraphicsProxyWidget* parent = nullptr);

    void SetAvailableParameters(const QList<QPair<QString, double>>& parameters);
};
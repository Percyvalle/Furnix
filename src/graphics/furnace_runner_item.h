#pragma once

#include "furnace_part_item.h"

class FurnaceRunnerItem : public FurnacePartItem
{
    Q_OBJECT
public:
    explicit FurnaceRunnerItem(QGraphicsItem* parent = nullptr);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // FurnacePartItem interface
public:
    void SetParameters(const FurnaceProfileParameters &parameters);

private:
    double m_width = 0.0;
    double m_height = 0.0;
};

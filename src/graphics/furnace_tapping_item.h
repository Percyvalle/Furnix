#pragma once

#include "furnace_part_item.h"

class FurnaceTappingItem : public FurnacePartItem
{
    Q_OBJECT
public:
    explicit FurnaceTappingItem(QGraphicsItem* parent = nullptr);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // FurnacePartItem interface
public:
    void SetParameters(const FurnaceProfileParameters &parameters);
};

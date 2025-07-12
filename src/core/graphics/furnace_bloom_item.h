#pragma once

#include "base_furnace_part_item.h"

class FurnaceBloomItem : public BaseFurnacePartItem
{
    Q_OBJECT
public:
    explicit FurnaceBloomItem(QGraphicsItem* parent = nullptr);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // FurnacePartItem interface
public:
    void SetParameters(const FurnaceProfileParameters &parameters) override;
    QList<QPair<QString, double>> GetAvailableParameters() override;
};


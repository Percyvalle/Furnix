#pragma once

#include "furnace_part_item.h"

class FurnaceShaftItem : public FurnacePartItem
{
    Q_OBJECT
public:
    explicit FurnaceShaftItem(QGraphicsItem* parent = nullptr);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // FurnacePartItem interface
public:
    void SetParameters(const FurnaceProfileParameters &parameters) override;
    QList<QPair<QString, double>> GetAvailableParameters() override;

private:
    double m_angle = 0.0;
    double m_top_width = 0.0;
    double m_buttom_width = 0.0;
};

#pragma once

#include <QGraphicsObject>

#include <models/furnace_profile_param.h>

class FurnacePartItem : public QGraphicsObject
{
    Q_OBJECT
public:
    enum PartType
    {
        Runner,
        Tapping,
        Bloom,
        Shoulder,
        Shaft
    } m_type;

    explicit FurnacePartItem(PartType type, QGraphicsItem* parent = nullptr);

    virtual void SetParameters(const FurnaceProfileParameters& parameters) = 0;

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

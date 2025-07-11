#include <QPainter>

#include "furnace_part_item.h"

FurnacePartItem::FurnacePartItem(PartType type, QGraphicsItem *parent)
    : QGraphicsObject(parent),
      m_type(type)
{}

void FurnacePartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(Qt::NoBrush);
}

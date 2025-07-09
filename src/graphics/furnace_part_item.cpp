#include "furnace_part_item.h"

FurnacePartItem::FurnacePartItem(PartType type, QGraphicsItem *parent)
    : QGraphicsObject(parent),
      m_type(type)
{}

void FurnacePartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

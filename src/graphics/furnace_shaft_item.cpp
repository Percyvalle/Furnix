#include "furnace_shaft_item.h"

FurnaceShaftItem::FurnaceShaftItem(QGraphicsItem *parent)
    : FurnacePartItem(FurnacePartItem::Shaft, parent)
{}

QRectF FurnaceShaftItem::boundingRect() const
{
    return QRectF(-m_width / 2, -m_height / 2, m_width, m_height);
}

void FurnaceShaftItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    FurnacePartItem::paint(painter, option, widget);
}

void FurnaceShaftItem::SetParameters(const FurnaceProfileParameters &parameters)
{
    m_width = parameters.shaftHeight / qSin(
                  qDegreesToRadians(parameters.shaftAngle));
    m_height = parameters.shaftHeight;
}

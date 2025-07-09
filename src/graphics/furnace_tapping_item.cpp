#include "furnace_tapping_item.h"

FurnaceTappingItem::FurnaceTappingItem(QGraphicsItem *parent)
    : FurnacePartItem(FurnacePartItem::Tapping, parent)
{}

QRectF FurnaceTappingItem::boundingRect() const
{
    return QRectF(-m_width / 2, -m_height / 2, m_width, m_height);
}

void FurnaceTappingItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    FurnacePartItem::paint(painter, option, widget);
}

void FurnaceTappingItem::SetParameters(const FurnaceProfileParameters &parameters)
{
    m_width = parameters.tappingDiameter;
    m_height = parameters.tappingHeight;
}

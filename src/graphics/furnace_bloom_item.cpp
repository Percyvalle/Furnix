#include "furnace_bloom_item.h"

FurnaceBloomItem::FurnaceBloomItem(QGraphicsItem *parent)
    : FurnacePartItem(FurnacePartItem::Bloom, parent)
{}

QRectF FurnaceBloomItem::boundingRect() const
{
    return QRectF(-m_width / 2, -m_height / 2, m_width, m_height);
}

void FurnaceBloomItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    FurnacePartItem::paint(painter, option, widget);
}

void FurnaceBloomItem::SetParameters(const FurnaceProfileParameters &parameters)
{
    m_width = parameters.bloomDiameter;
    m_height = parameters.bloomHeight;
}

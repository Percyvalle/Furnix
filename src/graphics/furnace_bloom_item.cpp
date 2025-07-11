#include "furnace_bloom_item.h"
#include "graphics/furnace_profile_item.h"

#include <QPainter>

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

    // Только boundingRect
    painter->drawRect(boundingRect());

    // Опционально: подпись координат
    painter->setPen(Qt::black);
    painter->drawText(boundingRect().topLeft() + QPointF(5, 15),
                      QString("(%1, %2)").arg(boundingRect().x()).arg(boundingRect().y()));
    painter->drawText(boundingRect().bottomRight() - QPointF(50, -15),
                      QString("(%1, %2)").arg(boundingRect().width()).arg(boundingRect().height()));
}

void FurnaceBloomItem::SetParameters(const FurnaceProfileParameters &parameters)
{
    m_width = parameters.bloomDiameter * FURNACE_PROFILE_SCALE;
    m_height = parameters.bloomHeight * FURNACE_PROFILE_SCALE;

    update();
}

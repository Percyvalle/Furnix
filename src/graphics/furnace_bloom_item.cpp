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

    painter->drawRect(boundingRect());
}

void FurnaceBloomItem::SetParameters(const FurnaceProfileParameters &parameters)
{
    m_width = parameters.bloomDiameter * FURNACE_PROFILE_SCALE;
    m_height = parameters.bloomHeight * FURNACE_PROFILE_SCALE;

    update();
}

QList<QPair<QString, double>> FurnaceBloomItem::GetAvailableParameters()
{
    QList<QPair<QString, double>> result = {
        {"Диаметр горна", m_width},
        {"Полная высота горна", m_height}
    };

    return result;
}

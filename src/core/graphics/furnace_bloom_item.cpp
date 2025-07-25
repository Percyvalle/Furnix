#include "furnace_bloom_item.h"
#include "furnace_profile_item.h"

#include <QPainter>

FurnaceBloomItem::FurnaceBloomItem(QGraphicsItem *parent)
    : BaseFurnacePartItem(BaseFurnacePartItem::Bloom, parent)
{}

QRectF FurnaceBloomItem::boundingRect() const
{
    return QRectF(-m_width / 2, -m_height / 2, m_width, m_height);
}

void FurnaceBloomItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    BaseFurnacePartItem::paint(painter, option, widget);

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
        {"Диаметр горна", m_width / FURNACE_PROFILE_SCALE},
        {"Полная высота горна", m_height / FURNACE_PROFILE_SCALE}
    };

    return result;
}

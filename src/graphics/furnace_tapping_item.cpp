#include "furnace_tapping_item.h"
#include "graphics/furnace_profile_item.h"

#include <QPainter>

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

    painter->drawRect(boundingRect());
}

void FurnaceTappingItem::SetParameters(const FurnaceProfileParameters &parameters)
{
    m_width = parameters.tappingDiameter * FURNACE_PROFILE_SCALE;
    m_height = parameters.tappingHeight * FURNACE_PROFILE_SCALE;

    update();
}

QList<QPair<QString, double>> FurnaceTappingItem::GetAvailableParameters()
{
    QList<QPair<QString, double>> result = {
        {"Высота распара", m_height / FURNACE_PROFILE_SCALE},
        {"Диаметр распара", m_width / FURNACE_PROFILE_SCALE}
    };

    return result;
}

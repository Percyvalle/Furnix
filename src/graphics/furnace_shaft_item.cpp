#include "furnace_shaft_item.h"
#include "graphics/furnace_profile_item.h"

#include <QPainter>

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

    painter->drawRect(boundingRect());

    // Опционально: подпись координат
    painter->setPen(Qt::black);
    painter->drawText(boundingRect().topLeft() + QPointF(5, 15),
                      QString("(%1, %2)").arg(boundingRect().x()).arg(boundingRect().y()));
    painter->drawText(boundingRect().bottomRight() - QPointF(50, -15),
                      QString("(%1, %2)").arg(boundingRect().width()).arg(boundingRect().height()));
}

void FurnaceShaftItem::SetParameters(const FurnaceProfileParameters &parameters)
{
    m_angle = parameters.shaftAngle;
    m_top_width = parameters.runnerDiameter * FURNACE_PROFILE_SCALE;
    m_buttom_width = parameters.tappingDiameter * FURNACE_PROFILE_SCALE;
    
    m_width = parameters.tappingDiameter * FURNACE_PROFILE_SCALE;
    m_height = parameters.shaftHeight * FURNACE_PROFILE_SCALE;

    update();
}

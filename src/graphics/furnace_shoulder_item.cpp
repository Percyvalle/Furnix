#include "furnace_shoulder_item.h"
#include "graphics/furnace_profile_item.h"

#include <QtMath>
#include <QPainter>

FurnaceShoulderItem::FurnaceShoulderItem(QGraphicsItem *parent)
    : FurnacePartItem(FurnacePartItem::Shoulder, parent)
{}

QRectF FurnaceShoulderItem::boundingRect() const
{
    return QRectF(-m_width / 2, -m_height / 2, m_width, m_height);
}

void FurnaceShoulderItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void FurnaceShoulderItem::SetParameters(const FurnaceProfileParameters &parameters)
{
    m_width = parameters.tappingDiameter * FURNACE_PROFILE_SCALE;
    m_height = parameters.shoulderHeight * FURNACE_PROFILE_SCALE;

    update();
}

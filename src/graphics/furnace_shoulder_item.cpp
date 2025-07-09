#include <QtMath>

#include "furnace_shoulder_item.h"

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
}

void FurnaceShoulderItem::SetParameters(const FurnaceProfileParameters &parameters)
{
    m_width = parameters.shoulderHeight / qSin(
                  qDegreesToRadians(parameters.shoulderAngleWithout));
    m_height = parameters.shoulderHeight;
}

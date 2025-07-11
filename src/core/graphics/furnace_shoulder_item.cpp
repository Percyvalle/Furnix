#include "furnace_shoulder_item.h"
#include "furnace_profile_item.h"

#include <QtMath>
#include <QPainter>

FurnaceShoulderItem::FurnaceShoulderItem(QGraphicsItem *parent)
    : BaseFurnacePartItem(BaseFurnacePartItem::Shoulder, parent)
{}

QRectF FurnaceShoulderItem::boundingRect() const
{
    return QRectF(-m_width / 2, 0, m_width, m_height);
}

void FurnaceShoulderItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    BaseFurnacePartItem::paint(painter, option, widget);

    QPainterPath path;
    path.moveTo(-m_top_width / 2, 0);
    path.lineTo(m_top_width / 2, 0);
    path.lineTo(m_buttom_width / 2, m_height);
    path.lineTo(-m_buttom_width / 2, m_height);
    path.closeSubpath();

    painter->drawPath(path);
}

void FurnaceShoulderItem::SetParameters(const FurnaceProfileParameters &parameters)
{
    m_angle = parameters.shoulderAngleWithout;
    m_top_width = parameters.tappingDiameter * FURNACE_PROFILE_SCALE;
    m_buttom_width = parameters.bloomDiameter * FURNACE_PROFILE_SCALE;

    m_width = qMax(m_top_width, m_buttom_width);
    m_height = parameters.shoulderHeight * FURNACE_PROFILE_SCALE;

    update();
}

QList<QPair<QString, double>> FurnaceShoulderItem::GetAvailableParameters()
{
    QList<QPair<QString, double>> result = {
        {"Высота заплечиков", m_height / FURNACE_PROFILE_SCALE},
        {"Угол наклона заплечиков", m_angle}
    };

    return result;
}
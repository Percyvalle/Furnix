#include "furnace_shaft_item.h"
#include "graphics/furnace_profile_item.h"

#include <QPainter>

FurnaceShaftItem::FurnaceShaftItem(QGraphicsItem *parent)
    : FurnacePartItem(FurnacePartItem::Shaft, parent)
{}

QRectF FurnaceShaftItem::boundingRect() const
{
    return QRectF(-m_width / 2, 0, m_width, m_height);
}

void FurnaceShaftItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    FurnacePartItem::paint(painter, option, widget);
    
    QPainterPath path;
    path.moveTo(-m_top_width / 2, 0);
    path.lineTo(m_top_width / 2, 0);
    path.lineTo(m_buttom_width / 2, m_height);
    path.lineTo(-m_buttom_width / 2, m_height);
    path.closeSubpath();
    
    painter->drawPath(path);
}

void FurnaceShaftItem::SetParameters(const FurnaceProfileParameters &parameters)
{
    prepareGeometryChange();

    m_angle = parameters.shaftAngle;
    m_top_width = parameters.runnerDiameter * FURNACE_PROFILE_SCALE;
    m_buttom_width = parameters.tappingDiameter * FURNACE_PROFILE_SCALE;
    
    m_width = qMax(m_top_width, m_buttom_width);
    m_height = parameters.shaftHeight * FURNACE_PROFILE_SCALE;

    update();
}

QList<QPair<QString, double>> FurnaceShaftItem::GetAvailableParameters()
{
    QList<QPair<QString, double>> result = {
        {"Высота шахты", m_height},
        {"Угол наклона шахты", m_angle}
    };

    return result;
}

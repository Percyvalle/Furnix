#include "furnace_profile_item.h"

#include <QPainter>

FurnaceProfileItem::FurnaceProfileItem(const FurnaceProfileParameters &parameters,
                                       QGraphicsItem *parent)
    : QGraphicsObject(parent),
      m_parameters(parameters),
      m_components(this)
{
    SetParameters(parameters);
}

void FurnaceProfileItem::SetParameters(const FurnaceProfileParameters &parameters)
{
    m_parameters = parameters;

    m_width = qMax(qMax(m_parameters.runnerDiameter,
                        m_parameters.tappingDiameter),
                   m_parameters.bloomDiameter) * FURNACE_PROFILE_SCALE;
    m_height = (m_parameters.runnerHeight + m_parameters.bloomHeight +
                m_parameters.tappingHeight + m_parameters.shaftHeight +
                m_parameters.shoulderHeight) * FURNACE_PROFILE_SCALE;

    m_components.m_bloom.SetParameters(m_parameters);
    m_components.m_shaft.SetParameters(m_parameters);
    m_components.m_runner.SetParameters(m_parameters);
    m_components.m_tapping.SetParameters(m_parameters);
    m_components.m_shoulder.SetParameters(m_parameters);
}

QRectF FurnaceProfileItem::boundingRect() const
{
    return QRectF(-m_width / 2, -m_height / 2, m_width, m_height);
}

void FurnaceProfileItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Только boundingRect
    painter->setPen(QPen(Qt::blue, 2)); // Синяя сплошная линия
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(boundingRect());

    // Опционально: подпись координат
    painter->setPen(Qt::black);
    painter->drawText(boundingRect().topLeft() + QPointF(5, 15),
                      QString("(%1, %2)").arg(boundingRect().x()).arg(boundingRect().y()));
    painter->drawText(boundingRect().bottomRight() - QPointF(50, -15),
                      QString("(%1, %2)").arg(boundingRect().width()).arg(boundingRect().height()));
}

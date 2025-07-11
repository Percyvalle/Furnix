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

    UpdatePositions();
}

void FurnaceProfileItem::UpdatePositions()
{
    const qreal centerX = 0;  // Центр по X
    qreal currentY = -m_height / 2;  // Начинаем с верха

    // 1. Runner (низ)
    m_components.m_runner.setPos(centerX, currentY + m_parameters.runnerHeight * FURNACE_PROFILE_SCALE / 2);
    currentY += m_parameters.runnerHeight * FURNACE_PROFILE_SCALE;

    // 2. Shaft (шахта)
    m_components.m_shaft.setPos(centerX, currentY);
    currentY += m_parameters.shaftHeight * FURNACE_PROFILE_SCALE;

    // 3. Tapping (летка) - теперь перед Shoulder и Bloom
    m_components.m_tapping.setPos(centerX, currentY + m_parameters.tappingHeight * FURNACE_PROFILE_SCALE / 2);
    currentY += m_parameters.tappingHeight * FURNACE_PROFILE_SCALE;

    // 4. Shoulder (переходник)
    m_components.m_shoulder.setPos(centerX, currentY);
    currentY += m_parameters.shoulderHeight * FURNACE_PROFILE_SCALE;

    // 5. Bloom (рабочая зона)
    m_components.m_bloom.setPos(centerX, currentY + m_parameters.bloomHeight * FURNACE_PROFILE_SCALE / 2);
    // currentY += m_parameters.bloomHeight * FURNACE_PROFILE_SCALE; // Не нужно, если это последний элемент
}

QRectF FurnaceProfileItem::boundingRect() const
{
    return QRectF(-m_width / 2, -m_height / 2, m_width, m_height);
}

void FurnaceProfileItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

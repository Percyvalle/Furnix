#include "furnace_runner_item.h"
#include "furnace_profile_item.h"

#include <QPainter>

FurnaceRunnerItem::FurnaceRunnerItem(QGraphicsItem *parent)
    : FurnacePartItem(FurnacePartItem::Runner, parent)
{}

QRectF FurnaceRunnerItem::boundingRect() const
{
    return QRectF(-m_width / 2, -m_height / 2, m_width, m_height);
}

void FurnaceRunnerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    FurnacePartItem::paint(painter, option, widget);

    painter->drawRect(boundingRect());
}

void FurnaceRunnerItem::SetParameters(const FurnaceProfileParameters &parameters)
{
    m_width = parameters.runnerDiameter * FURNACE_PROFILE_SCALE;
    m_height = parameters.runnerHeight * FURNACE_PROFILE_SCALE;

    update();
}

QList<QPair<QString, double>> FurnaceRunnerItem::GetAvailableParameters()
{
    QList<QPair<QString, double>> result = {
        {"Высота колошника", m_height / FURNACE_PROFILE_SCALE},
        {"Диаметр колошника", m_width / FURNACE_PROFILE_SCALE}
    };

    return result;
}

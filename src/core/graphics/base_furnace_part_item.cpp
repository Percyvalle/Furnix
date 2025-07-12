#include "base_furnace_part_item.h"

#include <QLabel>
#include <QPainter>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>

BaseFurnacePartItem::BaseFurnacePartItem(PartType type, QGraphicsItem *parent)
    : QGraphicsObject(parent),
      m_type(type)
{
    setAcceptHoverEvents(true);
}

void BaseFurnacePartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (isUnderMouse())
    {
        painter->setBrush(m_hoveredBrush);
    }

    painter->setPen(QPen(Qt::black, 3));
}

void BaseFurnacePartItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    UpdateTooltipPosition(event->scenePos());

    update();
    QGraphicsItem::hoverMoveEvent(event);
}

void BaseFurnacePartItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    ShowTooltip(event->scenePos());

    update();
    QGraphicsItem::hoverEnterEvent(event);
}

void BaseFurnacePartItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    HideTooltip();

    update();
    QGraphicsItem::hoverLeaveEvent(event);
}

void BaseFurnacePartItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void BaseFurnacePartItem::HideTooltip()
{
    if (m_tooltip)
    {
        m_tooltip->hide();
    }
}

void BaseFurnacePartItem::ShowTooltip(const QPointF &pos)
{
    if (!m_tooltip)
    {
        m_tooltip = QSharedPointer<FurnacePartTooltip>::create();
        m_tooltip->SetAvailableParameters(GetAvailableParameters());
        scene()->addItem(m_tooltip.get());
    }

    UpdateTooltipPosition(pos);
    m_tooltip->show();
}

void BaseFurnacePartItem::UpdateTooltipPosition(const QPointF &pos)
{
    if (!m_tooltip)
    {
        return;
    }

    QGraphicsView* view = scene()->views().first();
    const QRect viewportRect = view->viewport()->rect();
    const QPointF viewPos = view->mapFromScene(pos);
    
    const qreal tooltipWidth = m_tooltip->boundingRect().width();
    const qreal tooltipHeight = m_tooltip->boundingRect().height();
    
    QPointF newViewPos = viewPos + QPointF(15, 15);
    
    if (newViewPos.x() + tooltipWidth > viewportRect.right()) {
        newViewPos.setX(viewPos.x() - tooltipWidth - 15);
    }
    
    if (newViewPos.y() + tooltipHeight > viewportRect.bottom()) {
        newViewPos.setY(viewPos.y() - tooltipHeight - 15);
    }
    
    QPointF newScenePos = view->mapToScene(newViewPos.toPoint());
    m_tooltip->setPos(newScenePos);
}

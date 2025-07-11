#include "furnace_part_item.h"

#include <QLabel>
#include <QPainter>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>

FurnacePartItem::FurnacePartItem(PartType type, QGraphicsItem *parent)
    : QGraphicsObject(parent),
      m_type(type)
{
    setAcceptHoverEvents(true);
}

void FurnacePartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (isUnderMouse())
    {
        painter->setBrush(m_hoveredBrush);
    }

    painter->setPen(QPen(Qt::black, 3));
}

void FurnacePartItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    UpdateTooltipPosition(event->scenePos());

    update();
    QGraphicsItem::hoverMoveEvent(event);
}

void FurnacePartItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    ShowTooltip(event->scenePos());

    update();
    QGraphicsItem::hoverEnterEvent(event);
}

void FurnacePartItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    HideTooltip();

    update();
    QGraphicsItem::hoverLeaveEvent(event);
}

void FurnacePartItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void FurnacePartItem::HideTooltip()
{
    if (m_tooltip)
    {
        m_tooltip->hide();
    }
}

void FurnacePartItem::ShowTooltip(const QPointF &pos)
{
    if (!m_tooltip)
    {
        m_tooltip = QSharedPointer<FurnacePartTooltip>::create();
        scene()->addItem(m_tooltip.get());
    }

    UpdateTooltipPosition(pos);
    m_tooltip->show();
}

void FurnacePartItem::UpdateTooltipPosition(const QPointF &pos)
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

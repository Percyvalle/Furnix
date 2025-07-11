#include "zoom_graphics_view.h"

#include <QScrollBar>

ZoomGraphicsView::ZoomGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{}


void ZoomGraphicsView::wheelEvent(QWheelEvent *event)
{
    const double zoomFactor = 1.15;
    double scaleFactor = (event->angleDelta().y() > 0) ? zoomFactor : 1.0/zoomFactor;

    QTransform newTransform = transform().scale(scaleFactor, scaleFactor);
    if (newTransform.m11() < MIN_ZOOM_VALUE ||
        newTransform.m11() > MAX_ZOOM_VALUE)
    {
        return;
    }

    scale(scaleFactor, scaleFactor);
}

void ZoomGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        setCursor(Qt::ClosedHandCursor);
        m_isPanning = true;
        m_panningStartPosition = event->pos();
    }
    QGraphicsView::mousePressEvent(event);
}

void ZoomGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        setCursor(Qt::ClosedHandCursor);
    } else
    {
        setCursor(Qt::ArrowCursor);
    }

    if (m_isPanning)
    {
        QPointF delta = event->pos() - m_panningStartPosition;

        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());

        m_panningStartPosition = event->pos();
    }
    QGraphicsView::mouseMoveEvent(event);
}

void ZoomGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton &&
        m_isPanning)
    {
        m_isPanning = false;
        setCursor(Qt::ArrowCursor);
    }
    QGraphicsView::mouseReleaseEvent(event);
}

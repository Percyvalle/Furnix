#include "grid_scene.h"

#include <QPainter>

GridScene::GridScene(QObject *parent)
    : QGraphicsScene(parent)
{}

void GridScene::setGridSize(int size)
{
    if (size != m_gridSize && size > 0) {
        m_gridSize = size;
        update();
    }
}

void GridScene::setGridColor(const QColor &color)
{
    if (color != m_gridColor) {
        m_gridColor = color;
        update();
    }
}

void GridScene::setGridEnabled(bool enabled)
{
    if (enabled != m_gridEnabled) {
        m_gridEnabled = enabled;
        update();
    }
}

void GridScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter, rect);

    if (!m_gridEnabled || m_gridSize <= 0)
        return;

    painter->save();

    QPen pen(m_gridColor);
    pen.setWidthF(0.5);
    painter->setPen(pen);

    qreal left = std::floor(rect.left() / m_gridSize) * m_gridSize;
    qreal right = rect.right();
    for (qreal x = left; x < right; x += m_gridSize) {
        painter->drawLine(QPointF(x, rect.top()), QPointF(x, rect.bottom()));
    }

    qreal top = std::floor(rect.top() / m_gridSize) * m_gridSize;
    qreal bottom = rect.bottom();
    for (qreal y = top; y < bottom; y += m_gridSize) {
        painter->drawLine(QPointF(rect.left(), y), QPointF(rect.right(), y));
    }

    painter->restore();
}


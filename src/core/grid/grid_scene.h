#pragma once

#include <QGraphicsScene>

class GridScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GridScene(QObject *parent = nullptr);

    void setGridSize(int size);
    void setGridColor(const QColor &color);
    void setGridEnabled(bool enabled);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    int m_gridSize = 20;
    bool m_gridEnabled = true;
    QColor m_gridColor = Qt::gray;
};

#pragma once

#include <QGraphicsView>
#include <QWheelEvent>

class ZoomGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ZoomGraphicsView(QWidget* parent = nullptr);

protected:
    void wheelEvent(QWheelEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    const double MIN_ZOOM_VALUE = 0.5f;
    const double MAX_ZOOM_VALUE = 10.0f;

    bool m_isPanning = false;
    QPoint m_panningStartPosition;
};

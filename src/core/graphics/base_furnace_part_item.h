#pragma once

#include <QPair>
#include <QList>
#include <QSharedPointer>
#include <QGraphicsObject>

#include "furnace_part_tooltip.h"
#include "core/models/furnace_profile_param.h"

class BaseFurnacePartItem : public QGraphicsObject
{
    Q_OBJECT
public:
    enum PartType
    {
        Runner,
        Tapping,
        Bloom,
        Shoulder,
        Shaft
    } m_type;

    explicit BaseFurnacePartItem(PartType type, QGraphicsItem* parent = nullptr);

    virtual void SetParameters(const FurnaceProfileParameters& parameters) = 0;
    virtual QList<QPair<QString, double>> GetAvailableParameters() = 0;

    // QGraphicsItem interface
public:
    void paint(QPainter *paintZer, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    

protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

protected:
    double m_width = 0.0;
    double m_height = 0.0;
    QColor m_hoveredBrush = QColor(0, 0, 255, 77);
    
    // For FurnacePartTooltip
private:
    void HideTooltip();
    void ShowTooltip(const QPointF& pos);
    void UpdateTooltipPosition(const QPointF& pos);

    QSharedPointer<FurnacePartTooltip> m_tooltip = nullptr;
};

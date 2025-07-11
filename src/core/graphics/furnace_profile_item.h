#pragma once

#include <QGraphicsObject>

#include "core/entity/output_param_method.h"
#include "core/models/furnace_profile_param.h"

#include "furnace_bloom_item.h"
#include "furnace_runner_item.h"
#include "furnace_shaft_item.h"
#include "furnace_shoulder_item.h"
#include "furnace_tapping_item.h"

#define FURNACE_PROFILE_SCALE 20

class FurnaceProfileItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit FurnaceProfileItem(const FurnaceProfileParameters& parameters,
                                QGraphicsItem* parent = nullptr);

    void SetParameters(const FurnaceProfileParameters& parameters);

private:
    void UpdatePositions();

private:
    double m_width;
    double m_height;
    FurnaceProfileParameters m_parameters;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    struct FurnaceProfileComponents
    {
        FurnaceProfileComponents(QGraphicsItem* parent)
            : m_bloom(parent),
              m_shaft(parent),
              m_runner(parent),
              m_tapping(parent),
              m_shoulder(parent)
        {}

        FurnaceBloomItem m_bloom;
        FurnaceShaftItem m_shaft;
        FurnaceRunnerItem m_runner;
        FurnaceTappingItem m_tapping;
        FurnaceShoulderItem m_shoulder;
    } m_components;
};

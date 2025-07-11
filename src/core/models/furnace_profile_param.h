#pragma once

#include <QHash>
#include <QList>

#include "core/entity/output_param_method.h"

struct FurnaceProfileParameters
{
    double runnerHeight = 0.0;
    double runnerDiameter = 0.0;

    double tappingHeight = 0.0;
    double tappingDiameter = 0.0;

    double bloomDiameter = 0.0;
    double bloomHeight = 0.0;

    double shoulderHeight = 0.0;
    double shoulderAngleWithout = 0.0;

    double shaftHeight = 0.0;
    double shaftAngle = 0.0;
};

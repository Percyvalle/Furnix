#pragma once

#include "output_param_method.h"

class FurnaceParamMethod
{
public:
    FurnaceParamMethod(const QList<OutputParamMethod>& output);

    double getRunnerDiameter() const;
    double getRunnerHeight() const;
    double getShaftHeight() const;
    double getShaftAngle() const;
    double getShoulderAngleWithout() const;
    double getShoulderAngleWith() const;
    double getShoulderHeight() const;
    double getTappingDiameter() const;
    double getTappingHeight() const;
    double getBloomTotalHeight() const;
    double getBloomDiameter() const;
private:
    double m_bloomDiameter;
    double m_bloomTotalHeight;

    double m_tappingHeight;
    double m_tappingDiameter;

    double m_shoulderHeight;

    double m_shoulderAngleWith;
    double m_shoulderAngleWithout;

    double m_shaftAngle;
    double m_shaftHeight;

    double m_runnerHeight;
    double m_runnerDiameter;
};

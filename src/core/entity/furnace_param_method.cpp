#include "furnace_param_method.h"

FurnaceParamMethod::FurnaceParamMethod(const QList<OutputParamMethod> &output)
{

}

double FurnaceParamMethod::getRunnerDiameter() const
{
    return m_runnerDiameter;
}

double FurnaceParamMethod::getRunnerHeight() const
{
    return m_runnerHeight;
}

double FurnaceParamMethod::getShaftHeight() const
{
    return m_shaftHeight;
}

double FurnaceParamMethod::getShaftAngle() const
{
    return m_shaftAngle;
}

double FurnaceParamMethod::getShoulderAngleWithout() const
{
    return m_shoulderAngleWithout;
}

double FurnaceParamMethod::getShoulderAngleWith() const
{
    return m_shoulderAngleWith;
}

double FurnaceParamMethod::getShoulderHeight() const
{
    return m_shoulderHeight;
}

double FurnaceParamMethod::getTappingDiameter() const
{
    return m_tappingDiameter;
}

double FurnaceParamMethod::getTappingHeight() const
{
    return m_tappingHeight;
}

double FurnaceParamMethod::getBloomTotalHeight() const
{
    return m_bloomTotalHeight;
}

double FurnaceParamMethod::getBloomDiameter() const
{
    return m_bloomDiameter;
}

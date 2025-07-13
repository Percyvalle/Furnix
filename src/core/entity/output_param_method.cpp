#include "output_param_method.h"

OutputParamMethod::OutputParamMethod(QString name, double value, bool visible)
    : m_name(name), m_value(value), m_visible(visible)
{}

QString OutputParamMethod::getName() const
{
    return m_name;
}

double OutputParamMethod::getValue() const
{
    return m_value;
}

bool OutputParamMethod::isVisible() const
{
    return m_visible;
}

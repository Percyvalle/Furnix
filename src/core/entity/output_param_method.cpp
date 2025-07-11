#include "output_param_method.h"

OutputParamMethod::OutputParamMethod(QString name, double value)
    : m_name(name), m_value(value)
{}

QString OutputParamMethod::getName() const
{
    return m_name;
}

double OutputParamMethod::getValue() const
{
    return m_value;
}

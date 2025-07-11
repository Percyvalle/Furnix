#include "input_param_method.h"

InputParamMethod::InputParamMethod(QString name, double value)
    : m_name(name), m_value(value)
{}

QString InputParamMethod::getName() const
{
    return m_name;
}

double InputParamMethod::getValue() const
{
    return m_value;
}

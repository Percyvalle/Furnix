#pragma once

#include <QString>

class InputParamMethod
{
public:
    InputParamMethod(QString name, double value);

    QString getName() const;
    double getValue() const;

private:
    QString m_name;
    double m_value;
};


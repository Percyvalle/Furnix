#pragma once

#include <QString>

class OutputParamMethod
{
public:
    OutputParamMethod(QString name, double value);

    QString getName() const;
    double getValue() const;

private:
    QString m_name;
    double m_value;
};

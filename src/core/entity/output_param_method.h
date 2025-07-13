#pragma once

#include <QString>

class OutputParamMethod
{
public:
    OutputParamMethod() = default;
    OutputParamMethod(QString name, double value, bool visible);

    QString getName() const;
    double getValue() const;
    bool isVisible() const;

private:
    QString m_name;
    double m_value;
    bool m_visible;
};

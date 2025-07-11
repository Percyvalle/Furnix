#pragma once

#include <QString>

struct InputParametersData
{
    QString name;
    QString type;
    QString description;
    double defaultValue = 0.0f;
    bool required = false;
};

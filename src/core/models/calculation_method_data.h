#pragma once

#include "formula_parameters_data.h"
#include "input_parameters_data.h"
#include "output_parameters_data.h"

#include <QMap>
#include <QList>
#include <QString>

struct CalculationMethodData
{
    QString name;
    QString description;
    double version;

    QList<InputParametersData> input_parameters;
    QList<OutputParametersData> output_parameters;
    QList<FormulaParametersData> formular_parameters;

    QMap<QString, double> constant_parameters;
};

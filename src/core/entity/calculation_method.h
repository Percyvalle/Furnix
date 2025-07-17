#pragma once

#include <QString>

#include "core/models/calculation_method_data.h"

class CalculationMethod
{
public:
    CalculationMethod() = default;
    CalculationMethod(const CalculationMethodData& data);

    static CalculationMethod Load(const QString& path);

    QString getName() const;
    QString getDescription() const;
    double getVersion() const;
    QList<InputParametersData> getInputParameters() const;
    QList<OutputParametersData> getOutputParameters() const;
    QList<FormulaParametersData> getFormularParameters() const;
    QMap<QString, double> getConstantParameters() const;

private:
    QString name;
    QString description;
    double version;

    QList<InputParametersData> input_parameters;
    QList<OutputParametersData> output_parameters;
    QList<FormulaParametersData> formular_parameters;

    QMap<QString, double> constant_parameters;
};


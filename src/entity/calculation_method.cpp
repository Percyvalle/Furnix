#include "calculation_method.h"

#include <yaml-cpp/yaml.h>

#include "core/yaml/yaml_deserializer.h"

CalculationMethod::CalculationMethod(const CalculationMethodData &data)
{
    name = data.name;
    description = data.description;
    version = data.version;
    input_parameters = data.input_parameters;
    output_parameters = data.output_parameters;
    formular_parameters = data.formular_parameters;
    constant_parameters = data.constant_parameters;
}

CalculationMethod CalculationMethod::Load(const QString &path)
{
    YAML::Node node = YAML::LoadFile(path.toStdString());
    return CalculationMethod(node.as<CalculationMethodData>());
}

QString CalculationMethod::getName() const
{
    return name;
}

QString CalculationMethod::getDescription() const
{
    return description;
}

double CalculationMethod::getVersion() const
{
    return version;
}

QList<InputParametersData> CalculationMethod::getInputParameters() const
{
    return input_parameters;
}

QList<OutputParametersData> CalculationMethod::getOutputParameters() const
{
    return output_parameters;
}

QList<FormulaParametersData> CalculationMethod::getFormularParameters() const
{
    return formular_parameters;
}

QMap<QString, double> CalculationMethod::getConstantParameters() const
{
    return constant_parameters;
}

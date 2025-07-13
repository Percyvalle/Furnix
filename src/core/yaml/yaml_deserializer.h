#pragma once

#include <yaml-cpp/yaml.h>

#include "core/models/calculation_method_data.h"
#include "core/models/formula_parameters_data.h"
#include "core/models/output_parameters_data.h"
#include "core/models/input_parameters_data.h"

namespace YAML
{
template<>
struct convert<QString> {
    static bool decode(const Node& node, QString& rhs) {
        if (!node.IsScalar())
        {
            return false;
        }

        rhs = QString::fromStdString(node.as<std::string>());
        return true;
    }
};

template<typename T>
struct convert<QList<T>> {
    static bool decode(const Node& node, QList<T>& rhs) {
        if (!node.IsSequence())
        {
            return false;
        }

        rhs.clear();
        for (const auto& item : node) {
            rhs.push_back(item.as<T>());
        }

        return true;
    }
};

template<typename K, typename V>
struct convert<QMap<K, V>> {
    static bool decode(const Node& node, QMap<K, V>& rhs) {
        if (!node.IsMap())
        {
            return false;
        }

        rhs.clear();
        for (const auto& pair : node) {
            rhs.insert(pair.first.as<K>(), pair.second.as<V>());
        }

        return true;
    }
};

template<>
struct convert<InputParametersData>
{
    static bool decode(const Node& node, InputParametersData& rhs)
    {
        if (!node.IsMap())
        {
            return false;
        }

        rhs.name = node["name"].as<QString>();
        rhs.type = node["type"].as<QString>();
        rhs.description = node["description"].as<QString>();

        if (node["default"])
        {
            rhs.defaultValue = node["default"].as<double>();
        }

        if (node["required"])
        {
            rhs.required = node["required"].as<bool>();
        }

        return true;
    }
};

template<>
struct convert<OutputParametersData>
{
    static bool decode(const Node& node, OutputParametersData& rhs)
    {
        if (!node.IsMap())
        {
            return false;
        }

        rhs.name = node["name"].as<QString>();
        rhs.type = node["type"].as<QString>();
        rhs.description = node["description"].as<QString>();

        return true;
    }
};

template<>
struct convert<FormulaParametersData>
{
    static bool decode(const Node& node, FormulaParametersData& rhs)
    {
        if (!node.IsMap())
        {
            return false;
        }

        rhs.name = node["name"].as<QString>();
        rhs.expression = node["expression"].as<QString>();

        return true;
    }
};

template<>
struct convert<CalculationMethodData>
{
    static bool decode(const Node& node, CalculationMethodData& rhs)
    {
        if (!node.IsMap())
        {
            return false;
        }

        rhs.name = node["name"].as<QString>();
        rhs.version = node["version"].as<double>();
        rhs.description = node["description"].as<QString>();

        if (node["input_parameters"])
        {
            rhs.input_parameters = node["input_parameters"].as<QList<InputParametersData>>();
        }

        if (node["constants"])
        {
            rhs.constant_parameters = node["constants"].as<QMap<QString, double>>();
        }

        if (node["output_parameters"])
        {
            rhs.output_parameters = node["output_parameters"].as<QList<OutputParametersData>>();
        }

        if (node["formulas"])
        {
            rhs.formular_parameters = node["formulas"].as<QList<FormulaParametersData>>();
        }

        return true;
    }
};
}

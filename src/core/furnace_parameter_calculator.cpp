#include "furnace_parameter_calculator.h"

#include <muParser.h>

#include <QSet>
#include <QDebug>
#include <QString>

FurnaceParameterCalculator::FurnaceParameterCalculator() {}

QList<OutputParamMethod> FurnaceParameterCalculator::Calculate(
    const CalculationMethod &method,
    const QList<InputParamMethod> &input)
{
    mu::Parser parser;

    try
    {
        QSet<QString> visibleParamSet;
        for (const OutputParametersData& param : method.getOutputParameters())
        {
            visibleParamSet.insert(param.name);
        }

        QMap<std::wstring, double> localParamStorage;
        for (const InputParamMethod& param : input)
        {
            std::wstring name = param.getName().toStdWString();
            localParamStorage[name] = param.getValue();

            parser.DefineVar(name, &localParamStorage[name]);
        }

        QList<OutputParamMethod> outputList;
        QMap<QString, double> constantParams = method.getConstantParameters();
        for (const QString& param : constantParams.keys()) {
            parser.DefineVar(param.toStdWString(), &constantParams[param]);

            outputList.emplace_back(param, constantParams[param], visibleParamSet.contains(param));
        }

        for (const FormulaParametersData& formula : method.getFormularParameters())
        {
            parser.SetExpr(formula.expression.toStdWString());

            std::wstring name = formula.name.toStdWString();
            localParamStorage[name] = parser.Eval();

            parser.DefineVar(name, &localParamStorage[name]);

            outputList.emplace_back(formula.name, localParamStorage[name], visibleParamSet.contains(formula.name));
        }

        return outputList;
    }
    catch (mu::ParserError& exception)
    {
        qDebug() <<  exception.GetMsg();
        return QList<OutputParamMethod>();
    }
}

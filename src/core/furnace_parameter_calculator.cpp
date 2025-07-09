#include "furnace_parameter_calculator.h"

#include <muParser.h>

#include <QDebug>

FurnaceParameterCalculator::FurnaceParameterCalculator() {}

QList<OutputParamMethod> FurnaceParameterCalculator::Calculate(
    const CalculationMethod &method,
    const QList<InputParamMethod> &input)
{
    mu::Parser parser;

    try
    {
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

            outputList.emplace_back(param, constantParams[param]);
        }

        for (const FormulaParametersData& formula : method.getFormularParameters())
        {
            parser.SetExpr(formula.expression.toStdWString());

            std::wstring name = formula.name.toStdWString();
            localParamStorage[name] = parser.Eval();

            parser.DefineVar(name, &localParamStorage[name]);

            outputList.emplace_back(formula.name, localParamStorage[name]);
        }

        return outputList;
    }
    catch (mu::ParserError& exception)
    {
        qDebug() << exception.GetMsg();
    }
}

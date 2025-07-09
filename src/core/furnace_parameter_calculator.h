#pragma once

#include "entity/calculation_method.h"
#include "entity/input_param_method.h"
#include "entity/output_param_method.h"

class FurnaceParameterCalculator
{
public:
    FurnaceParameterCalculator();

    static QList<OutputParamMethod> Calculate(const CalculationMethod& method,
                                              const QList<InputParamMethod>& input);
};


#pragma once

#include <QObject>

#include <entity/calculation_method.h>

class IMethodsView
{
public:
    virtual ~IMethodsView() = default;

    virtual int AddMethod(const CalculationMethod& method) = 0;

    virtual void SetCurrentMethod(int index) = 0;
    virtual int CurrentMethodIndex() = 0;
};

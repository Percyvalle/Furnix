#pragma once

#include <QObject>

#include "models/furnace_profile_param.h"
#include "entity/output_param_method.h"

class FurnaceProfileLoader
{
public:
    FurnaceProfileLoader() = default;

    static FurnaceProfileParameters Load(QList<OutputParamMethod> output);
};


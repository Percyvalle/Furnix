#pragma once

#include <QObject>

#include "core/models/furnace_profile_param.h"
#include "core/entity/output_param_method.h"

class FurnaceProfileLoader
{
public:
    FurnaceProfileLoader() = default;

    static FurnaceProfileParameters Load(QList<OutputParamMethod> output);
};


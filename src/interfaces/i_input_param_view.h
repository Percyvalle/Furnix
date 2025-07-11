#pragma once

#include <QObject>

#include "core/entity/input_param_method.h"

class IInputParamView
{
public:
    virtual ~IInputParamView() = default;

    virtual QList<InputParamMethod> UploadInputParam(int index) = 0;
};

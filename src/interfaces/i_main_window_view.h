#pragma once

#include <QMainWindow>
#include <QObject>

#include "i_canvas_view.h"
#include "i_methods_view.h"
#include "i_input_param_view.h"

class IMainWindowView :
                        public ICanvasView,
                        public IMethodsView,
                        public IInputParamView
{
public:
    virtual ~IMainWindowView() = default;

    virtual QObject* asObject() = 0;
};

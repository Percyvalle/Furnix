#pragma once

#include <QMap>
#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>

#include "factories/component_factory.h"

#include "core/entity/input_param_method.h"
#include "core/models/input_parameters_data.h"

#define PROPERTY_NAME_STRING "parameterName"

class InputParametersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InputParametersWidget(QWidget* parent = nullptr);
    void LoadParameters(const QList<InputParametersData>& params);

    QList<InputParamMethod> GetValues() const;

private:
    QMap<QString, QLineEdit*> m_inputs;
}; 
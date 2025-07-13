#pragma once

#include <QList>
#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>

#include "factories/component_factory.h"

#include "core/models/output_parameters_data.h"
#include "core/entity/output_param_method.h"

#define PROPERTY_NAME_STRING "parameterName"
#define NAME_OUTPUT_LABEL_STRING "outputParameterLabel"

class OutputParametersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OutputParametersWidget(QWidget* parent = nullptr);
    void LoadParameters(const QList<OutputParametersData>& params);

    void UpdateValues(const QList<OutputParamMethod>& values);

private:
    QList<QLabel*> m_outputs;
};
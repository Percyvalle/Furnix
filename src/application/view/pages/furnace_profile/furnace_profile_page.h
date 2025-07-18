#pragma once

#include <QWidget>
#include <QStackedWidget>
#include <QGraphicsView>

#include "core/entity/calculation_method.h"
#include "core/entity/input_param_method.h"
#include "core/entity/output_param_method.h"
#include "core/models/input_parameters_data.h"
#include "core/models/output_parameters_data.h"

class FurnaceProfilePage : public QWidget
{
    Q_OBJECT
public:
    explicit FurnaceProfilePage(QWidget* parent = nullptr);

    void Initialize();

    int AddMethod(const CalculationMethod& method);

    void LoadInputParameters(const QList<InputParametersData>& params);
    void LoadOutputParameters(const QList<OutputParametersData>& params);
    void UpdateOutputParameters(const QList<OutputParamMethod>& params);

    QList<InputParamMethod> UploadInputParameters(int index) const;

public slots:
    void OnCalculationComplete(const QList<OutputParamMethod>& parameters);

signals:
    void InitializeTriggered();
    void CalculationTriggered(int);

private:
    QGraphicsView* m_furnaceProfileCanvas = nullptr;
    QStackedWidget* m_inputParametersStack = nullptr;
    QStackedWidget* m_outputParametersStack = nullptr;
};
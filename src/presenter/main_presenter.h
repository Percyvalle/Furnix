#pragma once

#include <QObject>


#include "interfaces/i_main_window_view.h"
#include "infrastructure/scanner/methods_scanner.h"

#include "core/entity/calculation_method.h"
#include "core/furnace_parameter_calculator.h"
#include "core/models/furnace_profile_param.h"

class MainPresenter : public QObject
{
    Q_OBJECT
public:
    explicit MainPresenter(IMainWindowView* view, QObject *parent = nullptr);

public slots:
    void OnCalculationMethod(int index);
    void OnInitializeComplete();

signals:
    void CalculationCompleteTriggered(const FurnaceProfileParameters& output);

private:
    IMainWindowView* m_view;

    QMap<int, CalculationMethod> m_loadedMethods;
};

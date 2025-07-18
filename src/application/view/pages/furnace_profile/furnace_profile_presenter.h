#pragma once

#include <QObject>

#include "furnace_profile_page.h"
#include "core/entity/calculation_method.h"
#include "core/furnace_parameter_calculator.h"
#include "infrastructure/scanner/methods_scanner.h"

class FurnaceProfilePresenter : public QObject
{
    Q_OBJECT
public:
    explicit FurnaceProfilePresenter(FurnaceProfilePage* view, 
                                     QObject* parent = nullptr);

public slots:
    void OnInitializeComplete();
    void OnCalculationMethod(int index);

signals:
    void CalculationCompleteTriggered(const QList<OutputParamMethod>& output);

private:
    FurnaceProfilePage* m_view;
    QMap<int, CalculationMethod> m_loadedMethods;
};
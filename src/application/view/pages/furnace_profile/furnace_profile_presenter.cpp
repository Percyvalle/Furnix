#include "furnace_profile_presenter.h"

FurnaceProfilePresenter::FurnaceProfilePresenter(FurnaceProfilePage *view, QObject *parent)
    : QObject(parent), m_view(view)
{
    connect(m_view, SIGNAL(InitializeTriggered()), this, SLOT(OnInitializeComplete()));
    connect(m_view, SIGNAL(CalculationTriggered(int)), this, SLOT(OnCalculationMethod(int)));
    connect(this, &FurnaceProfilePresenter::CalculationCompleteTriggered, m_view, &FurnaceProfilePage::OnCalculationComplete);
}

void FurnaceProfilePresenter::OnInitializeComplete()
{
    QStringList methods = MethodsScanner::scanAvailableMethods();

    for (const QString& method : methods)
    {
        try
        {
            CalculationMethod loadedMethod = CalculationMethod::Load(method);
            int index = m_view->AddMethod(loadedMethod);

            m_loadedMethods.insert(index, loadedMethod);

        }
        catch (std::exception& exception)
        {
            qWarning() << exception.what();
        }
    }
}

void FurnaceProfilePresenter::OnCalculationMethod(int index)
{
    if (!m_loadedMethods.contains(index))
    {
        return;
    }

    CalculationMethod selectedMethod = m_loadedMethods[index];
    QList<InputParamMethod> inputParameters = m_view->UploadInputParameters(index);

    QList<OutputParamMethod> outputParameters =
        FurnaceParameterCalculator::Calculate(selectedMethod, inputParameters);

    emit CalculationCompleteTriggered(outputParameters);
}
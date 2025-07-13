#include "main_presenter.h"

#include <QStringList>

#include "infrastructure/loaders/furnace_profile_loader.h"
#include "core/models/furnace_profile_param.h"

MainPresenter::MainPresenter(IMainWindowView *view, QObject *parent)
    : QObject(parent),
      m_view(view)
{
    connect(view->asObject(), SIGNAL(InitializeComplete()), this, SLOT(OnInitializeComplete()));
    connect(view->asObject(), SIGNAL(CalculationTriggered(int)), this, SLOT(OnCalculationMethod(int)));
    connect(this, SIGNAL(CalculationCompleteTriggered(const QList<OutputParamMethod>&)), view->asObject(), SLOT(OnCalculationComplete(const QList<OutputParamMethod>&)));
}

void MainPresenter::OnCalculationMethod(int index)
{
    auto method = m_loadedMethods.find(index);
    if (method == m_loadedMethods.end())
    {
        return;
    }

    CalculationMethod selectedMethod = method.value();
    QList<InputParamMethod> inputParameters = m_view->UploadInputParam(index);

    QList<OutputParamMethod> outputParameters =
        FurnaceParameterCalculator::Calculate(selectedMethod, inputParameters);

    emit CalculationCompleteTriggered(outputParameters);
}

void MainPresenter::OnInitializeComplete()
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

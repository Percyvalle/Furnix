#include "application_controller.h"

ApplicationController::ApplicationController(QObject *parent)
    : QObject{parent},
    m_mainPresenter(&m_mainWindow)
{}

bool ApplicationController::Run()
{
    if (!m_mainWindow.Initialize())
    {
        return false;
    }

    m_mainWindow.show();

    return true;
}

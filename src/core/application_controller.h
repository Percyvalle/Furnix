#pragma once
#include <QObject>

#include <view/main_window.h>
#include <presenter/main_presenter.h>

class ApplicationController : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationController(QObject *parent = nullptr);

    bool Run();

private:
    MainWindow m_mainWindow;
    MainPresenter m_mainPresenter;
};

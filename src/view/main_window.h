#pragma once

#include <QMainWindow>

#include "interfaces/i_main_window_view.h"
#include "core/models/furnace_profile_param.h"

#include <QButtonGroup>
#include <QLabel>
#include <QLineEdit>
#include <QStringList>
#include <QScrollArea>
#include <QHBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public IMainWindowView
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool Initialize();

public:
    // IInputParamView interface
    QList<InputParamMethod> UploadInputParam(int index);

    // IMethodsView interface
    int AddMethod(const CalculationMethod &method);
    void SetCurrentMethod(int index);
    int CurrentMethodIndex();

    // IMainWindowView interface
    QObject *asObject();

private:
    void SettingUpCanvas();
    void LoadInputParams(const QList<InputParametersData> &params);
    void LoadOutputParams(const QList<OutputParametersData> &params);
    void UpdateOutputParams(const QList<OutputParamMethod> &params);

public slots:
    void OnSwitchFeatures(int index);
    void OnSwitchInputParameters(int index);
    void OnSwitchOutputParameters(int index);
    void OnCalculationFurnaceProfile();
    void OnCalculationComplete(const QList<OutputParamMethod>& parameters);

signals:
    void InitializeComplete();
    void CalculationTriggered(int);

private:
    Ui::MainWindow *ui;
};

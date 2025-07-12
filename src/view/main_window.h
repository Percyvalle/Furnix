#pragma once

#include <QMainWindow>

#include "interfaces/i_main_window_view.h"
#include "core/entity/output_param_method.h"
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

    QScrollArea *createParametersScrollArea(const QList<InputParametersData> &params);
    QWidget *createParametersContainer(const QList<InputParametersData> &param);
    QHBoxLayout *createParameterRow(const InputParametersData &param);
    QLineEdit *createParameterInput(const InputParametersData &param);
    QLabel *createParameterLabel(const QString &text);

public slots:
    void OnSwitchFeatures(int index);
    void OnSwitchInputParameters(int index);
    void OnCalculationFurnaceProfile();
    void OnCalculationComplete(const FurnaceProfileParameters& parameters);

signals:
    void InitializeComplete();
    void CalculationTriggered(int);

private:
    Ui::MainWindow *ui;
};

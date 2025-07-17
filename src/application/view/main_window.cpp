#include "main_window.h"
#include "ui_main_window.h"

#include <QMap>

#include "input_parameters_widget.h"
#include "output_parameters_widget.h"

#include "factories/component_factory.h"

#include "core/grid/grid_scene.h"
#include "core/graphics/furnace_profile_item.h"

#include "infrastructure/scanner/methods_scanner.h"
#include "infrastructure/loaders/furnace_profile_loader.h"

enum CanvasStates : int
{
    CANVAS_FURNACE_PROFILE_INDEX = 0,
    CANVAS_LINING_STRUCTURE_INDEX = 1
};

#define CANVAS_WEIGHT_DEFAULT 1300
#define CANVAS_HEIGHT_DEFAULT 1300

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::Initialize()
{
    SettingUpCanvas();

    QButtonGroup* canvasButtonGroup = new QButtonGroup(this);
    canvasButtonGroup->setExclusive(true);

    // Must be added in index order!
    canvasButtonGroup->addButton(
        ui->canvas_furnace_profile, CanvasStates::CANVAS_FURNACE_PROFILE_INDEX);
    canvasButtonGroup->addButton(
        ui->canvas_lining_structure, CanvasStates::CANVAS_LINING_STRUCTURE_INDEX);

    connect(canvasButtonGroup, &QButtonGroup::idPressed, this, &MainWindow::OnSwitchFeatures);

    connect(ui->change_methods_combo_box, &QComboBox::currentIndexChanged, this, &MainWindow::OnSwitchInputParameters);
    connect(ui->change_methods_combo_box, &QComboBox::currentIndexChanged, this, &MainWindow::OnSwitchOutputParameters);
    connect(ui->calcualtion_furnace_profile, &QPushButton::clicked, this, &MainWindow::OnCalculationFurnaceProfile);

    emit InitializeComplete();

    return true;
}

void MainWindow::OnSwitchFeatures(int index)
{
    ui->user_stack->setCurrentIndex(index);
    ui->data_stack->setCurrentIndex(index);
    ui->canvas_stack->setCurrentIndex(index);
}

void MainWindow::OnSwitchInputParameters(int index)
{
    ui->furnace_profile_input_parameters->setCurrentIndex(index);
}

void MainWindow::OnSwitchOutputParameters(int index)
{
    ui->furnace_profile_output_parameters->setCurrentIndex(index);
}

void MainWindow::OnCalculationFurnaceProfile()
{
    emit CalculationTriggered(
            CurrentMethodIndex());
}

void MainWindow::OnCalculationComplete(const QList<OutputParamMethod>& parameters)
{
    UpdateOutputParams(parameters);

    FurnaceProfileItem* profileItem = new FurnaceProfileItem(
                                            FurnaceProfileLoader::Load(parameters));

    profileItem->setPos(ui->furnace_profile_canvas->scene()->sceneRect().width()/2,
                        ui->furnace_profile_canvas->scene()->sceneRect().height()/2);

    ui->furnace_profile_canvas->scene()->clear();
    ui->furnace_profile_canvas->scene()->addItem(profileItem);
}

void MainWindow::SettingUpCanvas()
{
    GridScene* canvasGridScene = new GridScene(ui->furnace_profile_canvas);
    canvasGridScene->setGridSize(15);
    canvasGridScene->setGridColor(Qt::lightGray);
    canvasGridScene->setBackgroundBrush(Qt::white);
    canvasGridScene->setSceneRect(0, 0, CANVAS_WEIGHT_DEFAULT, CANVAS_HEIGHT_DEFAULT);

    ui->furnace_profile_canvas->setScene(canvasGridScene);
}

void MainWindow::LoadInputParams(const QList<InputParametersData>& params)
{
    if (params.isEmpty()) {
        qWarning() << "Input parameters list is empty";
        return;
    }

    InputParametersWidget* container = new InputParametersWidget();
    container->LoadParameters(params);
    
    ui->furnace_profile_input_parameters->insertWidget(
        ui->change_methods_combo_box->count() - 1, ComponentFactory::CreateScrollArea(container));
}

void MainWindow::LoadOutputParams(const QList<OutputParametersData>& params)
{
    if (params.isEmpty())
    {
        qWarning() << "Output parameters list is empty";
        return;
    }

    OutputParametersWidget* container = new OutputParametersWidget();
    container->LoadParameters(params);

    ui->furnace_profile_output_parameters->insertWidget(
        ui->change_methods_combo_box->count() - 1, ComponentFactory::CreateScrollArea(container));
}

void MainWindow::UpdateOutputParams(const QList<OutputParamMethod> &params)
{
    int currentIndexMethod = CurrentMethodIndex();

    QScrollArea* scrollArea = qobject_cast<QScrollArea*>(
        ui->furnace_profile_output_parameters->widget(currentIndexMethod));

    if (!scrollArea) {
        qCritical() << "No scroll area at index" << currentIndexMethod;
        return;
    }

    QWidget* scrollWidget = scrollArea->widget();
    if (!scrollWidget) {
        qCritical() << "Scroll area at index" << currentIndexMethod << "has no widget";
        return;
    }
        
    OutputParametersWidget* outputWidget = qobject_cast<OutputParametersWidget*>(scrollWidget);
    if (!outputWidget) {
        qCritical() << "Widget in scroll area at index" << currentIndexMethod 
                    << "is not an OutputParametersWidget";
        return;
    }

    outputWidget->UpdateValues(params);
}

QList<InputParamMethod> MainWindow::UploadInputParam(int index)
{
    QScrollArea* scrollArea = qobject_cast<QScrollArea*>(
        ui->furnace_profile_input_parameters->widget(index));

    if (!scrollArea) {
        qCritical() << "No scroll area at index" << index;
        return {};
    }

    QWidget* scrollWidget = scrollArea->widget();
    if (!scrollWidget) {
        qCritical() << "Scroll area at index" << index << "has no widget";
        return {};
    }
        
    InputParametersWidget* inputWidget = qobject_cast<InputParametersWidget*>(scrollWidget);
    if (!inputWidget) {
        qCritical() << "Widget in scroll area at index" << index 
                    << "is not an InputParametersWidget";
        return {};
    }

    return inputWidget->GetValues();
}

int MainWindow::AddMethod(const CalculationMethod &method)
{
    int currentIndex = ui->change_methods_combo_box->count();

    ui->change_methods_combo_box->insertItem(currentIndex, method.getName());

    LoadInputParams(method.getInputParameters());
    LoadOutputParams(method.getOutputParameters());

    if ( ui->change_methods_combo_box->count() > 0)
    {
        ui->change_methods_combo_box->setCurrentIndex(0);
        ui->change_methods_combo_box->currentIndexChanged(0);
    }

    return currentIndex;
}

void MainWindow::SetCurrentMethod(int index)
{
    ui->change_methods_combo_box->setCurrentIndex(index);
}

int MainWindow::CurrentMethodIndex()
{
    return ui->change_methods_combo_box->currentIndex();
}

QObject *MainWindow::asObject()
{
    return this;
}

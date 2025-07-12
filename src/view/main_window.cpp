#include "main_window.h"
#include "ui_main_window.h"

#include "core/grid/grid_scene.h"
#include "core/graphics/furnace_profile_item.h"

#include "infrastructure/scanner/methods_scanner.h"

enum CanvasStates : int
{
    CANVAS_FURNACE_PROFILE_INDEX = 0,
    CANVAS_LINING_STRUCTURE_INDEX = 1
};

#define CANVAS_WEIGHT_DEFAULT 1300
#define CANVAS_HEIGHT_DEFAULT 1300

#define PROPERTY_NAME_INPUT_EDIT_STRING "parameterName"
#define NAME_INPUT_EDIT_STRING "inputParameterEdit"
#define NAME_INPUT_LABEL_STRING "inputParameterLabel"

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

void MainWindow::OnCalculationFurnaceProfile()
{
    emit CalculationTriggered(
            CurrentMethodIndex());
}

void MainWindow::OnCalculationComplete(const FurnaceProfileParameters &parameters)
{
    FurnaceProfileItem* profileItem = new FurnaceProfileItem(parameters);

    QPointF center(ui->furnace_profile_canvas->scene()->sceneRect().width()/2,
                   ui->furnace_profile_canvas->scene()->sceneRect().height()/2);
    profileItem->setPos(center);

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

    QScrollArea* scrollArea = createParametersScrollArea(params);
    ui->furnace_profile_input_parameters->insertWidget(
        ui->change_methods_combo_box->count() - 1, scrollArea);
}

QScrollArea* MainWindow::createParametersScrollArea(const QList<InputParametersData>& params)
{
    QWidget* container = createParametersContainer(params);
    
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(container);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("border: 0;");
    
    return scrollArea;
}

QWidget* MainWindow::createParametersContainer(const QList<InputParametersData>& params)
{
    QWidget* container = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(container);
    layout->setContentsMargins(10, 10, 10, 10);
    
    for (const InputParametersData& param : params) {
        layout->addLayout(createParameterRow(param));
    }
    
    layout->addStretch();
    
    return container;
}

QHBoxLayout* MainWindow::createParameterRow(const InputParametersData& param)
{
    QHBoxLayout* rowLayout = new QHBoxLayout();
    rowLayout->setContentsMargins(0, 0, 0, 0);

    QLabel* label = createParameterLabel(param.description);
    QLineEdit* input = createParameterInput(param);
    
    rowLayout->addWidget(label, 1);
    rowLayout->addWidget(input, 3);
    
    return rowLayout;
}

QLabel* MainWindow::createParameterLabel(const QString& text)
{
    QLabel* label = new QLabel(text);
    label->setObjectName(NAME_INPUT_LABEL_STRING);
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    label->setWordWrap(false);
    label->setToolTip(text);
    label->setMaximumWidth(200);
    
    return label;
}

QLineEdit* MainWindow::createParameterInput(const InputParametersData& param)
{
    QLineEdit* input = new QLineEdit(QString::number(param.defaultValue));
    input->setObjectName(NAME_INPUT_EDIT_STRING);
    input->setProperty(PROPERTY_NAME_INPUT_EDIT_STRING, param.name);
    input->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    input->setMaximumWidth(250);
    input->setMinimumWidth(150);
    
    return input;
}


QList<InputParamMethod> MainWindow::UploadInputParam(int index)
{
    QList<QLineEdit*> inputEditParams =
        ui->furnace_profile_input_parameters->widget(index)->findChildren<QLineEdit*>(NAME_INPUT_EDIT_STRING);

    QList<InputParamMethod> result;
    for (QLineEdit* edit : inputEditParams)
    {
        result.emplace_back(edit->property(PROPERTY_NAME_INPUT_EDIT_STRING).toString(), edit->text().toDouble());
    }

    return result;
}

int MainWindow::AddMethod(const CalculationMethod &method)
{
    int currentIndex = ui->change_methods_combo_box->count();

    ui->change_methods_combo_box->insertItem(currentIndex, method.getName());

    LoadInputParams(method.getInputParameters());

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


#include "main_window.h"
#include "ui_main_window.h"

#include <QButtonGroup>
#include <QLabel>
#include <QLineEdit>
#include <QStringList>

#include "core/grid/grid_scene.h"
#include "scanner/methods_scanner.h"

#include <graphics/furnace_profile_item.h>

#define CANVAS_FURNACE_PROFILE_INDEX 0
#define CANVAS_LINING_STRUCTURE_INDEX 1

#define CANVAS_WEIGHT_DEFAULT 1300
#define CANVAS_HEIGHT_DEFAULT 1300

#define PROPERTY_NAME_INPUT_EDIT_STRING "id"
#define NAME_INPUT_EDIT_STRING "input_edit"

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
        ui->canvas_furnace_profile, CANVAS_FURNACE_PROFILE_INDEX);
    canvasButtonGroup->addButton(
        ui->canvas_lining_structure, CANVAS_LINING_STRUCTURE_INDEX);

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
    qDebug() << "Furnace parameters:";
    qDebug() << "Runner height:" << parameters.runnerHeight;
    qDebug() << "Runner diameter:" << parameters.runnerDiameter;
    qDebug() << "Tapping height:" << parameters.tappingHeight;
    qDebug() << "Tapping diameter:" << parameters.tappingDiameter;
    qDebug() << "Bloom diameter:" << parameters.bloomDiameter;
    qDebug() << "Bloom height:" << parameters.bloomHeight;
    qDebug() << "Shoulder height:" << parameters.shoulderHeight;
    qDebug() << "Shoulder angle:" << parameters.shoulderAngleWithout;
    qDebug() << "Shaft height:" << parameters.shaftHeight;
    qDebug() << "Shaft angle:" << parameters.shaftAngle;

    FurnaceProfileItem* profileItem = new FurnaceProfileItem(parameters);

    QPointF center(ui->furnace_profile_canvas->scene()->sceneRect().width()/2,
                   ui->furnace_profile_canvas->scene()->sceneRect().height()/2);
    profileItem->setPos(center);

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

void MainWindow::LoadInputParams(const QList<InputParametersData> &params)
{
    QWidget* inputParametersPage = new QWidget();
    QVBoxLayout* inputParametersPageLayout = new QVBoxLayout(inputParametersPage);

    for (const InputParametersData& param : params)
    {
        QHBoxLayout* inputParametersRowLayout = new QHBoxLayout();

        QLabel* inputLabel = new QLabel(param.description);
        inputLabel->setObjectName("input_label");

        QLineEdit* inputLineEdit = new QLineEdit(
            QString::number(param.defaultValue));
        inputLineEdit->setObjectName(NAME_INPUT_EDIT_STRING);
        inputLineEdit->setProperty(PROPERTY_NAME_INPUT_EDIT_STRING, param.name);
        inputLineEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

        inputParametersRowLayout->addWidget(inputLabel);
        inputParametersRowLayout->addWidget(inputLineEdit);

        inputParametersPageLayout->addLayout(inputParametersRowLayout);
    }
    inputParametersPageLayout->addStretch();

    ui->furnace_profile_input_parameters->insertWidget(
        ui->change_methods_combo_box->count() - 1, inputParametersPage);
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


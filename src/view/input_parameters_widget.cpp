#include "input_parameters_widget.h"

InputParametersWidget::InputParametersWidget(QWidget *parent)
    : QWidget(parent)
{
}

void InputParametersWidget::LoadParameters(const QList<InputParametersData> &params)
{
    if (params.isEmpty())
    {
        return;
    }

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10);

    for (const InputParametersData& param : params) {
        QHBoxLayout* rowLayout = new QHBoxLayout();
        rowLayout->setContentsMargins(0, 0, 0, 0);

        QLabel* label = ComponentFactory::CreateLabel(param.description);
        QLineEdit* input = new QLineEdit(QString::number(param.defaultValue));
        input->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        input->setProperty(PROPERTY_NAME_STRING, param.name);
        input->setMaximumWidth(250);
        input->setMinimumWidth(150);
        
        rowLayout->addWidget(label, 1);
        rowLayout->addWidget(input, 3);

        layout->addLayout(rowLayout);

        m_inputs.insert(param.name, input);
    }
    layout->addStretch();
}

QList<InputParamMethod> InputParametersWidget::GetValues() const
{
    QList<InputParamMethod> result;
    for (const QLineEdit* edit : m_inputs.values())
    {
        result.emplace_back(
            edit->property(PROPERTY_NAME_STRING).toString(), 
            edit->text().toDouble());
    }

    return result;
}

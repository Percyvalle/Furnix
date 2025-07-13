#include "output_parameters_widget.h"

OutputParametersWidget::OutputParametersWidget(QWidget *parent)
    : QWidget(parent)
{
}

void OutputParametersWidget::LoadParameters(const QList<OutputParametersData>& params)
{
    if (params.isEmpty())
    {
        return;
    }

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10);

    for (const OutputParametersData& param : params) {
        QHBoxLayout* rowLayout = new QHBoxLayout();
        rowLayout->setContentsMargins(0, 0, 0, 0);

        QLabel* labelFirst = ComponentFactory::CreateLabel(param.description);
        QLabel* labelSecond = ComponentFactory::CreateLabel("-");
        labelSecond->setAlignment(Qt::AlignCenter);
        labelSecond->setProperty(PROPERTY_NAME_STRING, param.name);
        
        rowLayout->addWidget(labelFirst, 3);
        rowLayout->addWidget(labelSecond, 1);

        layout->addLayout(rowLayout);

        m_outputs.append(labelSecond);
    }
    layout->addStretch();
}

void OutputParametersWidget::UpdateValues(const QList<OutputParamMethod> &values)
{
    QMap<QString, OutputParamMethod> paramsMap;
    for (const OutputParamMethod& param : values)
    {
        paramsMap[param.getName()] = param;
    }

    for (QLabel* label : m_outputs)
    {
        QString name = label->property(PROPERTY_NAME_STRING).toString();
        if (paramsMap.contains(name))
        {
            label->setText(QString::number(paramsMap[name].getValue()));
            label->setToolTip(QString::number(paramsMap[name].getValue()));
        }
    }
}

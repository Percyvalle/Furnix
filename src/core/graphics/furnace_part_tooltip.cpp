#include "furnace_part_tooltip.h"

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

FurnacePartTooltip::FurnacePartTooltip(QGraphicsProxyWidget *parent)
    : QGraphicsProxyWidget(parent)
{
        setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
}

void FurnacePartTooltip::SetAvailableParameters(const QList<QPair<QString, double>> &parameters)
{
        QWidget* tooltipWidget = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout(tooltipWidget);
        
        QLabel* titleLabel = new QLabel("Furnace Part Information");
        titleLabel->setStyleSheet(
            "font-weight: bold;"
            "font-size: 14px;"
        );
        
        layout->addWidget(titleLabel);
        for (const QPair<QString, double>& info : parameters)
        {
            QLabel* contentLabel = new QLabel(
                QString("%1: %2")
                    .arg(info.first)
                    .arg(info.second)
            );
            contentLabel->setStyleSheet(
                "padding: 0px;"
                "padding-left: 7px;"
                "border: none;");

            layout->addWidget(contentLabel);
        }
        
        tooltipWidget->setStyleSheet(
            "background-color: #FFFFE0;"
            "border: 1px solid #C0C0C0;"
            "padding: 5px;"
        );
        
        setZValue(1000);
        setWidget(tooltipWidget);
        setWindowFlags(Qt::ToolTip);
}

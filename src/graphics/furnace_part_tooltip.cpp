#include "furnace_part_tooltip.h"

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

FurnacePartTooltip::FurnacePartTooltip(QGraphicsProxyWidget *parent)
    : QGraphicsProxyWidget(parent)
{
        setFlag(QGraphicsItem::ItemIgnoresTransformations, true);

            // Create a widget to hold our tooltip content
        QWidget* tooltipWidget = new QWidget();
        
        // Set up layout
        QVBoxLayout* layout = new QVBoxLayout(tooltipWidget);
        
        // Add test information
        QLabel* titleLabel = new QLabel("Furnace Part Information");
        titleLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
        
        QLabel* contentLabel = new QLabel(
            "Part: Heating Element\n"
            "Status: Operational\n"
            "Temperature: 750°C\n"
            "Material: Kanthal A-1\n"
            "Lifetime: 1200 cycles"
        );
        
        // Add widgets to layout
        layout->addWidget(titleLabel);
        layout->addWidget(contentLabel);
        
        // Set some styling
        tooltipWidget->setStyleSheet(
            "background-color: #FFFFE0;"
            "border: 1px solid #C0C0C0;"
            "padding: 5px;"
        );
        
        // Set the widget for this proxy
        setWidget(tooltipWidget);
        
        // Set some proxy properties
        setWindowFlags(Qt::ToolTip);
        setZValue(1000); // Make sure it appears on top
}
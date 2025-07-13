#include "component_factory.h"

QScrollArea *ComponentFactory::CreateScrollArea(QWidget *content)
{
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(content);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("border: 0;");
    
    return scrollArea;
}

QLabel *ComponentFactory::CreateLabel(const QString &text)
{
    QLabel* label = new QLabel(text);
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    label->setWordWrap(false);
    label->setToolTip(text);
    label->setMaximumWidth(200);

    return label;
}
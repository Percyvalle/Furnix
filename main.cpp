#include <QApplication>
#include <QStyleFactory>

#include "core/application_controller.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    QApplication::setStyle(
        QStyleFactory::create("Cleanlooks"));

    ApplicationController controller;
    if (!controller.Run())
    {
        return EXIT_FAILURE;
    }

    return application.exec();
}

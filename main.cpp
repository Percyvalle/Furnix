#include <QApplication>
#include <QStyleFactory>

#include <QDebug>
#include "core/application_controller.h"

int main(int argc, char *argv[])
{   
    try 
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
    catch (std::exception exception)
    {
        qCritical() << exception.what();
        return EXIT_FAILURE;
    }
}

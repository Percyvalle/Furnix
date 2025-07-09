#include <qdebug.h>

#include "furnace_profile_loader.h"

FurnaceProfileParameters FurnaceProfileLoader::Load(QList<OutputParamMethod> output)
{
    FurnaceProfileParameters parameters;

    try
    {
        static const QHash<QString, double*> fieldMap = {
            {"runnerHeight", &parameters.runnerHeight},
            {"runnerDiameter", &parameters.runnerDiameter},
            {"tappingHeight", &parameters.tappingHeight},
            {"tappingDiameter", &parameters.tappingDiameter},
            {"bloomDiameter", &parameters.bloomDiameter},
            {"bloomTotalHeight", &parameters.bloomHeight},
            {"shoulderHeight", &parameters.shoulderHeight},
            {"shoulderAngleWithout", &parameters.shoulderAngleWithout},
            {"shaftHeight", &parameters.shaftHeight},
            {"shaftAngle", &parameters.shaftAngle}
        };

        for (const auto& param : output) {
            auto it = fieldMap.find(param.getName());
            if (it != fieldMap.end()) {
                *it.value() = param.getValue();
            }
        }
    } catch (const std::exception& exception)
    {
        qCritical() << "Error loading data model: " << exception.what();
    }

    return parameters;
}



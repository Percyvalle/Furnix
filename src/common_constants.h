#pragma once

#include <QString>
#include <QStringList>

struct CommonConstants
{
    static const QString MethodsDirectory;

    static const QStringList YamlExtensions;
};

const QString CommonConstants::MethodsDirectory = "methods";

const QStringList CommonConstants::YamlExtensions = { "*.yaml", "*.yml" };

#include "methods_scanner.h"

#include <QDir>
#include <QCoreApplication>

#include "common_constants.h"

QString MethodsScanner::getMethodsDir()
{
    return QDir(QCoreApplication::applicationDirPath())
        .filePath(CommonConstants::MethodsDirectory);
}

QStringList MethodsScanner::scanAvailableMethods()
{
    QDir methodsDir = getMethodsDir();

    QStringList methods;
    if (!methodsDir.exists())
    {
        return methods;
    }

    const QList<QFileInfo> methodFilesInfo = methodsDir.entryInfoList(CommonConstants::YamlExtensions, QDir::Files);
    for (const QFileInfo& info : methodFilesInfo)
    {
        methods.append(info.absoluteFilePath());
    }

    return methods;
}

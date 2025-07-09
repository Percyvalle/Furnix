#pragma ocne

#include <QObject>
#include <QVector>
#include <QString>
#include <QStringList>

class MethodsScanner : public QObject
{
public:
    static QString getMethodsDir();
    static QStringList scanAvailableMethods();
};


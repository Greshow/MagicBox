#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QJsonObject>
#include <QString>

class ConfigManager {
public:
    static QJsonObject loadOrCreateConfig(const QString& filePath);
    static void saveConfig(const QString& filePath, const QJsonObject& config);
};

#endif // CONFIGMANAGER_H
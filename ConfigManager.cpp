#include "ConfigManager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>

QJsonObject ConfigManager::loadOrCreateConfig(const QString& filePath) {
    QFile file(filePath);
    if (!file.exists() || file.size() == 0) {
        QJsonObject defaultConfig;
        QJsonArray defaultButtons;
        QJsonObject defaultButton1;
        defaultButton1["name"] = "记事本";
        defaultButton1["command"] = "notepad.exe";
        defaultButtons.append(defaultButton1);
        defaultConfig["默认分类"] = defaultButtons;

        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(nullptr, "错误", "无法创建配置文件！");
            return QJsonObject();
        }
        file.write(QJsonDocument(defaultConfig).toJson());
        file.close();
        return defaultConfig;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(nullptr, "错误", "无法打开配置文件！");
        return QJsonObject();
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || doc.isEmpty()) {
        QMessageBox::critical(nullptr, "错误", "配置文件内容无效！");
        return QJsonObject();
    }
    return doc.object();
}

void ConfigManager::saveConfig(const QString& filePath, const QJsonObject& config) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(nullptr, "错误", "无法保存配置文件！");
        return;
    }
    file.write(QJsonDocument(config).toJson());
    file.close();
}
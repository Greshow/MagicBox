#ifndef BUTTONMANAGER_H
#define BUTTONMANAGER_H

#include <QWidget>
#include <QJsonObject>

class ButtonManager {
public:
    static void createButtons(const QString& category, QWidget* buttonsWidget, const QJsonObject& config);
    static void refreshCategories(QWidget* categoriesWidget, QWidget* buttonsWidget, const QJsonObject& config);
};

#endif // BUTTONMANAGER_H
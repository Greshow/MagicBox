#include "ButtonManager.h"
#include "DialogManager.h"
#include "ConfigManager.h"
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QProcess>
#include <QLayout>
#include <QJsonArray>

void ButtonManager::createButtons(const QString& category, QWidget* buttonsWidget, const QJsonObject& config) {
    QLayout* layout = buttonsWidget->layout();
    if (layout) {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    }

    QJsonArray buttons = config[category].toArray();
    for (const QJsonValue& buttonValue : buttons) {
        QJsonObject button = buttonValue.toObject();
        QString name = button["name"].toString();
        QString command = button["command"].toString();
        auto btn = new QPushButton(name, buttonsWidget);

        btn->setContextMenuPolicy(Qt::CustomContextMenu);
        QObject::connect(btn, &QPushButton::customContextMenuRequested, [btn, buttonsWidget, category, name, command]() {
            QMenu menu;
            QAction* modifyAction = menu.addAction("修改");
            QAction* deleteAction = menu.addAction("删除");

            QAction* selectedAction = menu.exec(btn->mapToGlobal(QPoint(0, btn->height())));
            if (selectedAction == modifyAction) {
                DialogManager::ButtonDialog dialog(name, command, buttonsWidget);
                if (dialog.exec() == QDialog::Accepted) {
                    QString newName = dialog.getName();
                    QString newCommand = dialog.getCommand();
                    if (!newName.isEmpty() && !newCommand.isEmpty()) {
                        QJsonObject config = ConfigManager::loadOrCreateConfig("config.json");
                        QJsonArray buttons = config[category].toArray();

                        for (QJsonValueRef buttonValue : buttons) {
                            QJsonObject button = buttonValue.toObject();
                            if (button["name"] == name && button["command"] == command) {
                                button["name"] = newName;
                                button["command"] = newCommand;
                                buttonValue = button;
                                break;
                            }
                        }
                        config[category] = buttons;
                        ConfigManager::saveConfig("config.json", config);
                        createButtons(category, buttonsWidget, ConfigManager::loadOrCreateConfig("config.json"));
                    }
                }
            }
            else if (selectedAction == deleteAction) {
                QJsonObject config = ConfigManager::loadOrCreateConfig("config.json");
                QJsonArray buttons = config[category].toArray();

                for (int i = 0; i < buttons.size(); i++) {
                    QJsonObject button = buttons[i].toObject();
                    if (button["name"] == name && button["command"] == command) {
                        buttons.removeAt(i);
                        break;
                    }
                }
                config[category] = buttons;
                ConfigManager::saveConfig("config.json", config);
                createButtons(category, buttonsWidget, ConfigManager::loadOrCreateConfig("config.json"));
            }
            });

        QObject::connect(btn, &QPushButton::clicked, [command]() {
            QProcess::startDetached(command);
            });
        layout->addWidget(btn);
    }

    auto addButton = new QPushButton("新增按钮", buttonsWidget);
    QObject::connect(addButton, &QPushButton::clicked, [buttonsWidget, category]() {
        DialogManager::ButtonDialog dialog("", "", buttonsWidget);
        if (dialog.exec() == QDialog::Accepted) {
            QString name = dialog.getName();
            QString command = dialog.getCommand();
            if (!name.isEmpty() && !command.isEmpty()) {
                QJsonObject config = ConfigManager::loadOrCreateConfig("config.json");
                QJsonArray buttons = config[category].toArray();

                QJsonObject newButton;
                newButton["name"] = name;
                newButton["command"] = command;
                buttons.append(newButton);
                config[category] = buttons;

                ConfigManager::saveConfig("config.json", config);
                createButtons(category, buttonsWidget, ConfigManager::loadOrCreateConfig("config.json"));
            }
        }
        });
    layout->addWidget(addButton);
}

void ButtonManager::refreshCategories(QWidget* categoriesWidget, QWidget* buttonsWidget, const QJsonObject& config) {
    QLayout* layout = categoriesWidget->layout();
    if (layout) {
        // 清空布局中的所有内容
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    }

    // 添加现有的分类按钮
    for (const QString& category : config.keys()) {
        auto btn = new QPushButton(category, categoriesWidget);

        btn->setContextMenuPolicy(Qt::CustomContextMenu);
        QObject::connect(btn, &QPushButton::customContextMenuRequested, [btn, categoriesWidget, buttonsWidget, category]() {
            QMenu menu;
            QAction* modifyAction = menu.addAction("修改");
            QAction* deleteAction = menu.addAction("删除");

            QAction* selectedAction = menu.exec(btn->mapToGlobal(QPoint(0, btn->height())));
            if (selectedAction == modifyAction) {
                DialogManager::CategoryDialog dialog(category, categoriesWidget);
                if (dialog.exec() == QDialog::Accepted) {
                    QString newName = dialog.getName();
                    if (!newName.isEmpty()) {
                        QJsonObject config = ConfigManager::loadOrCreateConfig("config.json");
                        QJsonArray buttons = config[category].toArray();
                        config.remove(category);
                        config[newName] = buttons;
                        ConfigManager::saveConfig("config.json", config);
                        refreshCategories(categoriesWidget, buttonsWidget, ConfigManager::loadOrCreateConfig("config.json"));
                    }
                }
            }
            else if (selectedAction == deleteAction) {
                QJsonObject config = ConfigManager::loadOrCreateConfig("config.json");
                config.remove(category);
                ConfigManager::saveConfig("config.json", config);
                refreshCategories(categoriesWidget, buttonsWidget, ConfigManager::loadOrCreateConfig("config.json"));
            }
            });

        QObject::connect(btn, &QPushButton::clicked, [=]() {
            createButtons(category, buttonsWidget, config);
            });
        layout->addWidget(btn);
    }

    // 添加“新增分类”按钮
    auto addCategoryButton = new QPushButton("新增分类", categoriesWidget);
    QObject::connect(addCategoryButton, &QPushButton::clicked, [categoriesWidget, buttonsWidget]() {
        DialogManager::CategoryDialog dialog("", categoriesWidget);
        if (dialog.exec() == QDialog::Accepted) {
            QString categoryName = dialog.getName();
            if (!categoryName.isEmpty()) {
                QJsonObject config = ConfigManager::loadOrCreateConfig("config.json");
                config[categoryName] = QJsonArray(); // 创建一个空的分类
                ConfigManager::saveConfig("config.json", config);
                refreshCategories(categoriesWidget, buttonsWidget, ConfigManager::loadOrCreateConfig("config.json"));
            }
        }
        });
    layout->addWidget(addCategoryButton); // 将“新增分类”按钮添加到布局底部
}
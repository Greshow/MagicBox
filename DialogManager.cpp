#include "DialogManager.h"

// CategoryDialog 实现
DialogManager::CategoryDialog::CategoryDialog(const QString& currentName, QWidget* parent) : QDialog(parent) {
    setWindowTitle(currentName.isEmpty() ? "新增分类" : "修改分类");
    QFormLayout* formLayout = new QFormLayout(this);
    nameEdit = new QLineEdit(currentName, this);
    formLayout->addRow("分类名称:", nameEdit);

    QPushButton* saveButton = new QPushButton("保存", this);
    connect(saveButton, &QPushButton::clicked, this, &CategoryDialog::accept);
    formLayout->addRow(saveButton);
}

QString DialogManager::CategoryDialog::getName() const {
    return nameEdit->text();
}

// ButtonDialog 实现
DialogManager::ButtonDialog::ButtonDialog(const QString& currentName, const QString& currentCommand, QWidget* parent) : QDialog(parent) {
    setWindowTitle(currentName.isEmpty() ? "新增按钮" : "修改按钮");
    QFormLayout* formLayout = new QFormLayout(this);
    nameEdit = new QLineEdit(currentName, this);
    commandEdit = new QLineEdit(currentCommand, this);
    formLayout->addRow("名称:", nameEdit);
    formLayout->addRow("命令:", commandEdit);

    QPushButton* saveButton = new QPushButton("保存", this);
    connect(saveButton, &QPushButton::clicked, this, &ButtonDialog::accept);
    formLayout->addRow(saveButton);
}

QString DialogManager::ButtonDialog::getName() const {
    return nameEdit->text();
}

QString DialogManager::ButtonDialog::getCommand() const {
    return commandEdit->text();
}
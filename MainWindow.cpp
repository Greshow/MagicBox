#include "MainWindow.h"
#include "ButtonManager.h"
#include "ConfigManager.h"
#include "DialogManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFile>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setupUI();
    loadConfig();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    centralWidget = new QWidget(this);
    auto mainLayout = new QHBoxLayout(centralWidget);

    // 左侧分类区域（添加滚动条）
    categoriesScrollArea = new QScrollArea(centralWidget);
    categoriesScrollArea->setWidgetResizable(true);
    categoriesWidget = new QWidget();
    auto categoriesLayout = new QVBoxLayout(categoriesWidget);
    categoriesWidget->setLayout(categoriesLayout);
    categoriesScrollArea->setWidget(categoriesWidget);

    // 右侧按钮区域（添加滚动条）
    buttonsScrollArea = new QScrollArea(centralWidget);
    buttonsScrollArea->setWidgetResizable(true);
    buttonsWidget = new QWidget();
    auto buttonsLayout = new QVBoxLayout(buttonsWidget);
    buttonsWidget->setLayout(buttonsLayout);
    buttonsScrollArea->setWidget(buttonsWidget);

    // 将左右区域添加到主布局
    mainLayout->addWidget(categoriesScrollArea, 1);
    mainLayout->addWidget(buttonsScrollArea, 3);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::loadConfig() {
    QJsonObject config = ConfigManager::loadOrCreateConfig("config.json");
    ButtonManager::refreshCategories(categoriesWidget, buttonsWidget, config);
}
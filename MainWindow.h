#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void setupUI();
    void loadConfig();

    QWidget* centralWidget;
    QScrollArea* categoriesScrollArea;
    QScrollArea* buttonsScrollArea;
    QWidget* categoriesWidget;
    QWidget* buttonsWidget;
};

#endif // MAINWINDOW_H
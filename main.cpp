#include <QApplication>
#include "MainWindow.h"
#include <windows.h>

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(65001);
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("动态按钮工具");
    window.setGeometry(100, 100, 600, 400);
    window.show();

    return app.exec();
}
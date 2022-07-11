#include "main_window.hpp"
#include<QApplication>


int main(int argc, char **argv) {
    QApplication app(argc, argv);
    AC_MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
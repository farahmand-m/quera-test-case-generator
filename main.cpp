#include <QApplication>
#include <QMainWindow>
#include "MainWindow.hpp"
#include "TestCase.hpp"
#define APPNAME "QTC Generator"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName(APPNAME);
    app.setDesktopFileName(APPNAME);
    app.setApplicationDisplayName(APPNAME);
    app.setOrganizationName("mFarahmand.ir");
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
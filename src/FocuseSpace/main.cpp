#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMainWindow>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.setStyleSheet( " background-color: #303030; " );
    mainWindow.setWindowTitle(" ~ focuse space ~ ");
    mainWindow.setWindowIcon(QIcon("images/home.svg"));
    mainWindow.show();
    return a.exec();
}

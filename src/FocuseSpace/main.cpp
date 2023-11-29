#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QSqlQuery>
#include <QDebug>

static bool createConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");

    db.setUserName("admin");
    db.setHostName("localhost");
    db.setPassword("password");

    if(!db.open()) {
        qDebug() << db.lastError();
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(createConnection() == false) {
        return -1;
    }

    MainWindow mainWindow;
    mainWindow.setStyleSheet( " background-color: #303030; " );
    mainWindow.setWindowTitle(" ~ focuse space ~ ");
    mainWindow.setWindowIcon(QIcon("://home.svg"));
    mainWindow.show();
    return a.exec();
}

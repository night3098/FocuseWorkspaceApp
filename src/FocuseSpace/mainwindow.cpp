#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
{
    setWindowTitle(" ~ focuse space ~ ");
    setFixedSize(700, 350);

    statusBar = new QStatusBar(this);

    imageLabel = new QLabel(this);
    QPixmap image("://tasks.png");
    imageLabel->setGeometry(50, 50, 300, 300);
    imageLabel->setPixmap(image);

    titleMain = new QLabel("HOME PAGE", this);
    titleMain->setGeometry(300, 30, 400, 60);
    titleMain->setAlignment(Qt::AlignCenter);
    titleMain->setFont(QFont("SF Pro Black", 30));
    titleMain->setStyleSheet( " color: #ffffff; " );

    openTasks = new QPushButton("TASKS", this);
    openTasks->setGeometry(350, 150, 300, 40);
    openTasks->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-radius: 10px; border-style: solid; border-color: #444444; alternate-background-color: #303030;" );
    openTasks->setFont(QFont("SF Pro Black", 12));

    connect(openTasks, SIGNAL(clicked()), this, SLOT(openTasksWin()));

    openNotes = new QPushButton("NOTES", this);
    openNotes->setGeometry(350, 200, 300, 40);
    openNotes->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-radius: 10px; border-style: solid; border-color: #444444; alternate-background-color: #303030;" );
    openNotes->setFont(QFont("SF Pro Black", 12));

    connect(openNotes, SIGNAL(clicked()), this, SLOT(openNotesWin()));

    openTimer = new QPushButton("POMODORO", this);
    openTimer->setGeometry(350, 250, 300, 40);
    openTimer->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-radius: 10px; border-style: solid; border-color: #444444; alternate-background-color: #303030;" );
    openTimer->setFont(QFont("SF Pro Black", 12));

    connect(openTimer, SIGNAL(clicked()), this, SLOT(openPomodoroWin()));

    setStatusBar(statusBar);

    qDebug() << "OK";
    statusBar->showMessage("OK");
}

MainWindow::~MainWindow()
{
}

void MainWindow::openTasksWin() {
    hide();
    tasks_window = new Tasks(this);
    tasks_window->setWindowIcon(QIcon("://tasks.svg"));
    tasks_window->show();
}

void MainWindow::openNotesWin() {
    hide();
    notes_window = new Notes(this);
    notes_window->setWindowIcon(QIcon("://notes.svg"));
    notes_window->show();
}

void MainWindow::openPomodoroWin() {
    //hide();
    pomodoro_window = new Pomodoro(this);
    pomodoro_window->setWindowIcon(QIcon("://pomodoro.svg"));
    pomodoro_window->show();
}

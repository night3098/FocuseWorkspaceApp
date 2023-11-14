#include "ui_tasks.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDialog>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>

Tasks::Tasks(QMainWindow *parent) : QMainWindow(parent) 
{
    setWindowTitle("~ tasks ~");
    setFixedSize(400, 560);
    
    winTitle = new QLabel("TASKS", this);
    winTitle->setGeometry(0, 30, 400, 60);
    winTitle->setAlignment(Qt::AlignCenter);
    winTitle->setFont(QFont("SF Pro Black", 30));
    winTitle->setStyleSheet( " color: #ffffff; " );

    taskList = new QListWidget(this);
    taskList->setStyleSheet( " background-color: #303030; color: #ffffff; border-color: #ffffff; alternate-background-color: #303030;" );
    taskList->setGeometry(50, 100, 300, 290);
    taskList->setFont(QFont("SF Pro Black", 10));

    taskInput = new QLineEdit(this);
    taskInput->setStyleSheet( " background-color: #303030; color: #ffffff; border-color: #ffffff; alternate-background-color: #303030;" );
    taskInput->setFont(QFont("SF Pro Black", 10));
    taskInput->setGeometry(50, 400, 300, 40);

    addButton = new QPushButton("ADD TASK", this);
    addButton->setStyleSheet( " background-color: #303030; color: #ffffff; border-color: #ffffff; alternate-background-color: #303030;" );
    addButton->setFont(QFont("SF Pro Black", 10));
    addButton->setGeometry(50, 450, 150, 40);
    connect(addButton, SIGNAL(clicked()), this, SLOT(addTask()));

    removeButton = new QPushButton("DONE", this);
    removeButton->setStyleSheet( " background-color: #303030; color: #ffffff; border-color: #ffffff; alternate-background-color: #303030;" );
    removeButton->setFont(QFont("SF Pro Black", 10));
    removeButton->setGeometry(200, 450, 150, 40);
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeTask()));

    backButton = new QPushButton("BACK", this);
    backButton->setStyleSheet( " background-color: #303030; color: #ffffff; border-color: #ffffff; alternate-background-color: #303030;" );
    backButton->setFont(QFont("SF Pro Black", 10));
    backButton->setGeometry(50, 500, 300, 40);
    connect(backButton, SIGNAL(clicked()), this, SLOT(toMainWindow()));
}

void Tasks::addTask() {
    QString task = taskInput->text();
    if (!task.isEmpty()) {
        taskList->addItem(task);
        taskInput->clear();
    }
}

void Tasks::removeTask() {
    qDeleteAll(taskList->selectedItems());
}


void Tasks::toMainWindow() {
    close();
    MainWindow *mainWindow = new MainWindow(this);
    mainWindow->setWindowIcon(QIcon("images/home.svg"));
    mainWindow->show();
}
#include "ui_tasks.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDialog>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidgetItem>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

Tasks::Tasks(QMainWindow *parent) : QMainWindow(parent)
{
    setWindowTitle("~ tasks ~");
    setFixedSize(800, 600);
    
    tasksdb = QSqlDatabase::addDatabase("QSQLITE");
    tasksdb.setDatabaseName("../tasks.db");

    if(tasksdb.open()) {
        qDebug() << "OK" << tasksdb.databaseName();
    }
    else{
        qDebug() << "Error [TASKS DB] -> " << tasksdb.lastError();
    }

    winTitle = new QLabel("TASKS", this);
    winTitle->setGeometry(0, 30, 800, 60);
    winTitle->setAlignment(Qt::AlignCenter);
    winTitle->setFont(QFont("SF Pro Black", 30));
    winTitle->setStyleSheet( " color: #ffffff; " );

    taskList = new QListWidget(this);
    taskList->setStyleSheet( " background-color: #393939; selection-background-color: #999999; selection-color: #ffffff; color: #ffffff;border-width: 2px; border-style: solid; border-radius: 10px; border-color: #600900; alternate-background-color: #600900;" );
    taskList->setGeometry(50, 100, 340, 360);
    taskList->setFont(QFont("SF Pro Black", 12));

    doneList = new QListWidget(this);
    doneList->setStyleSheet( " background-color: #393939; selection-background-color: #999999; selection-color: #ffffff; color: #ffffff;border-width: 2px; border-style: solid; border-radius: 10px; border-color: #006018; alternate-background-color: #303030;" );
    doneList->setGeometry(410, 100, 340, 360);
    doneList->setFont(QFont("SF Pro Black", 12));

    taskInput = new QLineEdit(this);
    taskInput->setStyleSheet( " background-color: #393939; selection-background-color: #999999; selection-color: #ffffff; color: #ffffff;border-width: 2px; border-style: solid; border-radius: 10px; border-color: #393939; alternate-background-color: #303030;" );
    taskInput->setFont(QFont("SF Pro Black", 15));
    taskInput->setGeometry(50, 480, 700, 40);
    taskInput->setAlignment(Qt::AlignCenter);
    taskInput->setPlaceholderText("Task");

    removeButton = new QPushButton("DONE", this);
    removeButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #444444; alternate-background-color: #303030;" );
    removeButton->setFont(QFont("SF Pro Black", 10));
    removeButton->setGeometry(170, 540, 100, 40);
    connect(removeButton, SIGNAL(clicked()), this, SLOT(moveTask()));

    clearTask = new QPushButton("REMOVE", this);
    clearTask->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #444444; alternate-background-color: #303030;" );
    clearTask->setFont(QFont("SF Pro Black", 10));
    clearTask->setGeometry(50, 540, 100, 40);
    connect(clearTask, SIGNAL(clicked()), this, SLOT(removeTask()));

    backButton = new QPushButton("BACK", this);
    backButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #444444; alternate-background-color: #303030;" );
    backButton->setFont(QFont("SF Pro Black", 10));
    backButton->setGeometry(300, 540, 200, 40);
    connect(backButton, SIGNAL(clicked()), this, SLOT(toMainWindow()));

    addButton = new QPushButton("ADD TASK", this);
    addButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #444444; alternate-background-color: #303030;" );
    addButton->setFont(QFont("SF Pro Black", 10));
    addButton->setGeometry(530, 540, 100, 40);
    connect(addButton, SIGNAL(clicked()), this, SLOT(addTask()));

    removeButton = new QPushButton("REMOVE", this);
    removeButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #444444; alternate-background-color: #303030;" );
    removeButton->setFont(QFont("SF Pro Black", 10));
    removeButton->setGeometry(650, 540, 100, 40);
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeDone()));
}

void Tasks::addTask() {
    QString task = taskInput->text();
    if (!task.isEmpty()) {
        taskList->addItem(task);
        taskInput->clear();
    }
}

void Tasks::moveTask() {
    QListWidgetItem *item = taskList->takeItem(taskList->currentRow());
    doneList->addItem(item);
}

void Tasks::removeTask() {
    qDeleteAll(taskList->selectedItems());
}

void Tasks::removeDone() {
    //qDeleteAll(doneList->selectedItems());
    doneList->clear();
}

void Tasks::toMainWindow() {
    QSqlDatabase::database().close();
    QSqlDatabase::removeDatabase("QSQLITE");

    close();
    MainWindow *mainWindow = new MainWindow(this);
    mainWindow->setWindowIcon(QIcon("images/home.svg"));
    mainWindow->show();
}

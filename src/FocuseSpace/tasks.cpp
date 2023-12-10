#include "tasks.h"
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
#include <QSqlRecord>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSettings>

Tasks::Tasks(QMainWindow *parent) : QMainWindow(parent)
{
    QSettings settings("Tasks", "Tasks");
    restoreGeometry(settings.value("geometry").toByteArray());

// DATABASE

    QString str = "CREATE TABLE donetasks ( "
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "task VARCHAR(300)"
                  ");";

    if (!query.exec(str)) {
        qDebug() << query.lastError();
    }
    else {
        qDebug() << "Таблица donetasks создана";
    }


    QString str2 = "CREATE TABLE tasks ( "
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "task VARCHAR (300)"
                  ");";

    if (!query.exec(str2)) {
        qDebug() << query.lastError();
    }
    else {
        qDebug() << "Таблица tasks создана";
    }


// UI
    setWindowTitle("~ tasks ~");
    //setFixedSize(800, 600);
    setMinimumSize(600, 400);

    
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *titleLayout = new QHBoxLayout;
    QHBoxLayout *tasksLayout = new QHBoxLayout;
    QHBoxLayout *buttonsLayout = new QHBoxLayout;

    mainLayout->setSpacing(10);

    statusBar = new QStatusBar(this);

    taskLabel = new QLabel("TASKS", this);
    //taskLabel->setGeometry(150, 30, 100, 60);
    taskLabel->setAlignment(Qt::AlignCenter);
    taskLabel->setFont(QFont("SF Pro Black", 20));
    taskLabel->setStyleSheet( " color: #ffffff; " );

    doneLabel = new QLabel("DONE", this);
    //doneLabel->setGeometry(520, 30, 100, 60);
    doneLabel->setAlignment(Qt::AlignCenter);
    doneLabel->setFont(QFont("SF Pro Black", 20));
    doneLabel->setStyleSheet( " color: #ffffff; " );

    taskList = new QListWidget(this);
    taskList->setStyleSheet( " background-color: #393939; selection-background-color: #999999; selection-color: #ffffff; color: #ffffff;border-width: 5px; border-style: solid; border-radius: 10px; border-color: #393939; alternate-background-color: #600900;" );
    //taskList->setGeometry(50, 100, 340, 360);
    taskList->setMinimumSize(50, 50);
    taskList->setFont(QFont("SF Pro Black", 12));
    connect(taskList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(moveToDone(QListWidgetItem*)));

    doneList = new QListWidget(this);
    doneList->setStyleSheet( " background-color: #393939; selection-background-color: #999999; selection-color: #ffffff; color: #ffffff;border-width: 5px; border-style: solid; border-radius: 10px; border-color: #393939; alternate-background-color: #303030;" );
    //doneList->setGeometry(410, 100, 340, 360);
    doneList->setMinimumSize(50, 50);
    doneList->setFont(QFont("SF Pro Black", 12));
    connect(doneList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(moveToTasks(QListWidgetItem*)));

    taskInput = new QLineEdit(this);
    taskInput->setStyleSheet( " background-color: #393939; selection-background-color: #999999; selection-color: #ffffff; color: #ffffff;border-width: 5px; border-style: solid; border-radius: 10px; border-color: #393939; alternate-background-color: #303030;" );
    taskInput->setFont(QFont("SF Pro Black", 12));
    //taskInput->setGeometry(50, 480, 700, 40);
    taskInput->setMinimumSize(50, 40);
    taskInput->setAlignment(Qt::AlignCenter);
    taskInput->setPlaceholderText("Task");
    connect(taskInput, &QLineEdit::returnPressed, [=]{
        QString title = taskInput->text();
        
        if(title.isEmpty()) {
            qDebug() << "Task is empty";
            statusBar->showMessage("Task is empty");
        }
        else {
            addTask();
        }
    });

    clearTask = new QPushButton("REMOVE", this);
    clearTask->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #444444; alternate-background-color: #303030;" );
    clearTask->setFont(QFont("SF Pro Black", 10));
    //clearTask->setGeometry(50, 540, 100, 40);
    clearTask->setMinimumSize(40, 40);
    connect(clearTask, SIGNAL(clicked()), this, SLOT(removeTask()));

    backButton = new QPushButton("BACK", this);
    backButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #444444; alternate-background-color: #303030;" );
    backButton->setFont(QFont("SF Pro Black", 10));
    //backButton->setGeometry(300, 540, 200, 40);
    backButton->setMinimumSize(40, 40);
    connect(backButton, SIGNAL(clicked()), this, SLOT(toMainWindow()));

    removeButton = new QPushButton("REMOVE", this);
    removeButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #444444; alternate-background-color: #303030;" );
    removeButton->setFont(QFont("SF Pro Black", 10));
    //removeButton->setGeometry(650, 540, 100, 40);
    removeButton->setMinimumSize(40, 40);
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeDone()));

    setStatusBar(statusBar);

    titleLayout->addWidget(taskLabel);
    titleLayout->addWidget(doneLabel);

    tasksLayout->addWidget(taskList);
    tasksLayout->addWidget(doneList);

    buttonsLayout->addWidget(clearTask);
    buttonsLayout->addWidget(backButton);
    buttonsLayout->addWidget(removeButton);

    mainLayout->addLayout(titleLayout);
    mainLayout->addLayout(tasksLayout);
    mainLayout->addWidget(taskInput);
    mainLayout->addLayout(buttonsLayout);

    query.exec("SELECT * FROM tasks");
    while (query.next()) {
        int id = query.value("id").toInt();
        QString text = query.value("task").toString();

        QListWidgetItem *item = new QListWidgetItem(text);
        item->setData(Qt::UserRole, id);
        taskList->addItem(item);

        qDebug() << "Tasks list was loaded";

        statusBar->showMessage("All tasks was loaded");
    }

    query.exec("SELECT * FROM donetasks");
    while (query.next()) {
        int id = query.value("id").toInt();
        QString text = query.value("task").toString();

        QListWidgetItem *item = new QListWidgetItem(text);
        item->setData(Qt::UserRole, id);
        doneList->addItem(item);

        qDebug() << "Tasks list was loaded";

        statusBar->showMessage("All tasks was loaded");
    }


}

// FUNCTIONAL
Tasks::~Tasks() {
    QSettings settings("Tasks", "Tasks");
    settings.setValue("geometry", saveGeometry());
    delete ui;
}


void Tasks::addTask() {
    QString task = taskInput->text();
    if (!task.isEmpty()) {
        taskList->addItem(task);
        taskInput->clear();
    }

    if(!query.exec("INSERT INTO tasks (task) VALUES('"+task+"');")) {
        qDebug() << query.lastError();
    }
    else {
        qDebug() << task << " was saved";
        statusBar->showMessage(task + " was saved");
    }
}

void Tasks::moveToDone(QListWidgetItem *item) {
    QString done = item->text();

    if(!query.exec("INSERT INTO donetasks (task) VALUES('"+done+"');")) {
        qDebug() << query.lastError();
    }
    else {
        QListWidgetItem *item = taskList->takeItem(taskList->currentRow());
        doneList->addItem(item);
        qDebug() << done << " was moved";
        statusBar->showMessage(done + " was moved");
    }

    QString task = item->text();

    query.prepare("DELETE FROM tasks WHERE task = '"+task+"'");

    if (query.exec()) {
        qDebug() << done << " was moved";
        statusBar->showMessage(done + " was moved");
    } else {
        qDebug() << "Error deleting data:" << query.lastError().text();
        statusBar->showMessage(query.lastError().text());
    }
}

void Tasks::moveToTasks(QListWidgetItem *item) {
    QString task = item->text();

    if(!query.exec("INSERT INTO tasks (task) VALUES('"+task+"');")) {
        qDebug() << query.lastError();
    }
    else {
        QListWidgetItem *item = doneList->takeItem(doneList->currentRow());
        taskList->addItem(item);
        qDebug() << task << " was moved";
        statusBar->showMessage(task + " was moved");
    }

    QString done = item->text();

    query.prepare("DELETE FROM donetasks WHERE task = '"+done+"'");

    if (query.exec()) {
        qDebug() << done << " was moved";
        statusBar->showMessage(done + " was moved");
    } else {
        qDebug() << "Error deleting data:" << query.lastError().text();
        statusBar->showMessage(query.lastError().text());
    }
}

void Tasks::removeTask() {
    QListWidgetItem *item = taskList->takeItem(taskList->currentRow());

    QString task = item->text();

    query.prepare("DELETE FROM tasks WHERE task = '"+task+"'");

    if (query.exec()) {
        qDebug() << task << " was deleted";
        statusBar->showMessage(task + " was deleted");
    } else {
        qDebug() << "Error deleting data:" << query.lastError().text();
        statusBar->showMessage(query.lastError().text());
    }
}

void Tasks::removeDone() {
    QListWidgetItem *item = doneList->takeItem(doneList->currentRow());

    QString task = item->text();

    query.prepare("DELETE FROM donetasks WHERE task = '"+task+"'");

    if (query.exec()) {
        qDebug() << task << " was deleted";
        statusBar->showMessage(task + " was deleted");
    } else {
        qDebug() << "Error deleting data:" << query.lastError().text();
        statusBar->showMessage(query.lastError().text());
    }
}

void Tasks::toMainWindow() {
    QSettings settings("Tasks", "Tasks");
    settings.setValue("geometry", saveGeometry());

    close();
    MainWindow *mainWindow = new MainWindow(this);
    mainWindow->setWindowIcon(QIcon("://home.svg"));
    mainWindow->show();
}

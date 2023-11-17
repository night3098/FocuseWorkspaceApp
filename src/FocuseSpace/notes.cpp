#include "notes.h"
#include "ui_notes.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QTextEdit>
#include <QMainWindow>

Notes::Notes(QMainWindow *parent) :
    QMainWindow(parent)
{
    setWindowTitle("~ notes ~");
    resize(800, 650);

    title = new QLabel("Notes", this);
    title->setGeometry(0, 20, 800, 50);
    title->setAlignment(Qt::AlignCenter);
    title->setFont(QFont("SF Pro Black", 30));
    title->setStyleSheet( " color: #ffffff; " );

    noteEdit = new QTextEdit(this);
    noteEdit->setGeometry(380, 80, 400, 500);
    //noteEdit->setAlignment(Qt::AlignCenter);
    noteEdit->setStyleSheet( " color: #ffffff; " );


    saveButton = new QPushButton("SAVE", this);
    saveButton->setGeometry(605, 595, 175, 40);
    saveButton->setStyleSheet( " background-color: #303030; color: #ffffff; border-color: #ffffff; alternate-background-color: #303030; selection-background-color: #303030;" );
    saveButton->setFont(QFont("SF Pro Black", 10));

    editButton = new QPushButton("EDIT", this);
    editButton->setGeometry(20, 595, 175, 40);
    editButton->setStyleSheet( " background-color: #303030; color: #ffffff; border-color: #ffffff; alternate-background-color: #303030; selection-background-color: #303030;" );
    editButton->setFont(QFont("SF Pro Black", 10));

    backButton = new QPushButton("BACK", this);
    backButton->setGeometry(215, 595, 175, 40);
    backButton->setStyleSheet( " background-color: #303030; color: #ffffff; border-color: #ffffff; alternate-background-color: #303030; selection-background-color: #303030;" );
    backButton->setFont(QFont("SF Pro Black", 10));
    connect(backButton, SIGNAL(clicked()), this, SLOT(toMainWindow()));

    removeButton = new QPushButton("REMOVE", this);
    removeButton->setGeometry(410, 595, 175, 40);
    removeButton->setStyleSheet( " background-color: #303030; color: #ffffff; border-color: #ffffff; alternate-background-color: #303030; selection-background-color: #303030;" );
    removeButton->setFont(QFont("SF Pro Black", 10));
}

Notes::~Notes() {
    delete ui;
}


void Notes::toMainWindow() {
    close();
    MainWindow *mainWindow = new MainWindow(this);
    mainWindow->setWindowIcon(QIcon("images/home.svg"));
    mainWindow->show();
}
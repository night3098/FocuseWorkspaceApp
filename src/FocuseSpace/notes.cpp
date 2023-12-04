#include "notes.h"
#include "ui_notes.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QTextEdit>
#include <QMainWindow>
#include <QListWidgetItem>
#include <QListWidget>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

Notes::Notes(QMainWindow *parent) :
    QMainWindow(parent)
{

    QSqlQuery query;
    QString str = "CREATE TABLE notes ( "
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "name VARCHAR(100),"
                  "text VARCHAR(999999999)"
                  ");";

    if (!query.exec(str)) {
        qDebug() << query.lastError();
    }
    else {
        qDebug() << "Таблица notes создана";
    }

    setWindowTitle("~ notes ~");
    setFixedSize(800, 720);

    title = new QLabel("Notes", this);
    title->setGeometry(0, 20, 800, 50);
    title->setAlignment(Qt::AlignCenter);
    title->setFont(QFont("SF Pro Black", 30));
    title->setStyleSheet( " color: #ffffff; " );

    noteName = new QLineEdit(this);
    noteName->setGeometry(280, 80, 500, 50);
    noteName->setFont(QFont("SF Pro Black", 14));
    noteName->setStyleSheet( " background-color: #393939; selection-background-color: #999999; selection-color: #ffffff; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #393939; alternate-background-color: #303030;" );
    noteName->setPlaceholderText("Title");

    noteEdit = new QTextEdit(this);
    noteEdit->setGeometry(280, 150, 500, 500);
    noteEdit->setStyleSheet( " background-color: #393939; selection-background-color: #999999; selection-color: #ffffff; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #393939; alternate-background-color: #303030;" );
    noteEdit->setFont(QFont("SF Pro Black", 11));
    noteEdit->setPlaceholderText("Note");

    notesList = new QListWidget(this);
    notesList->setGeometry(20, 80, 240, 570);
    notesList->setStyleSheet( " background-color: #393939; selection-background-color: #999999; selection-color: #ffffff; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #393939; alternate-background-color: #303030;" );
    notesList->setFont(QFont("SF Pro Black", 12));
    connect(notesList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(doubleClick(QListWidgetItem*)));

    saveButton = new QPushButton("SAVE", this);
    saveButton->setGeometry(480, 665, 295, 40);
    saveButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #444444; alternate-background-color: #303030;" );
    saveButton->setFont(QFont("SF Pro Black", 10));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveNotes()));

    backButton = new QPushButton("BACK", this);
    backButton->setGeometry(20, 665, 235, 40);
    backButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #444444; alternate-background-color: #303030;" );
    backButton->setFont(QFont("SF Pro Black", 10));
    connect(backButton, SIGNAL(clicked()), this, SLOT(toMainWindow()));

    removeButton = new QPushButton("REMOVE", this);
    removeButton->setGeometry(280, 665, 175, 40);
    removeButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #444444; alternate-background-color: #303030;" );
    removeButton->setFont(QFont("SF Pro Black", 10));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeNote()));


    query.exec("SELECT * FROM notes");
    while (query.next()) {
        QString name = query.value("name").toString();
//        QString text = query.value("text").toString();

//        QString note = name + text;

//        QListWidgetItem *item = new QListWidgetItem(note);
        QListWidgetItem *item = new QListWidgetItem(name);
        notesList->addItem(item);

        qDebug() << name << " was loaded";
    }
}


Notes::~Notes() {
    delete ui;
}

void Notes::toMainWindow() {
    close();
    MainWindow *mainWindow = new MainWindow(this);
    mainWindow->setWindowIcon(QIcon("://home.svg"));
    mainWindow->show();
}

void Notes::saveNotes() {
    QString text = noteEdit->toPlainText();
    if(!text.isEmpty()) {
        QSqlQuery query;

        QString title = noteName->text();
        QString note = title + text;
        QString nnnn = title;

        QString exec = "INSERT INTO notes (name, text) VALUES('"+nnnn+"', '"+text+"');";

        if(!query.exec(exec)) {
            qDebug() << query.lastError();
        }
        else {
            qDebug() << title << " was saved";
        }

        noteEdit->clear();
        noteName->clear();

        QListWidgetItem *item = new QListWidgetItem(title);
        notesList->addItem(item);
    }
    else {
        qDebug() << "Note is empty";
    }
}

void Notes::doubleClick(QListWidgetItem *item) {
    QSqlQuery query;

    QListWidgetItem *selectedItem = notesList->currentItem();
    
    QString note = selectedItem->text();

    QString name = selectedItem->text();

    query.exec("SELECT * FROM notes WHERE name = '"+name+"'");

    if (query.exec()) {
        while (query.next()) {
            QString name = query.value("name").toString();
            QString text = query.value("text").toString();

            noteName->setText(name);
            noteEdit->setText(text);

            qDebug() << name << " was opened";
        }
    }else {
        qDebug() << "Error moving data: " << query.lastError().text();
    }


        query.prepare("DELETE FROM notes WHERE name = '"+name+"'");

        if (query.exec()) {
            delete notesList->takeItem(notesList->row(item));
            qDebug() << name << " was opened";
        } else {
            qDebug() << "Error moving data: " << query.lastError().text();
        }
}


void Notes::removeNote() {
    QSqlQuery query;
    
    QListWidgetItem *selectedItem = notesList->currentItem();

    QString name = selectedItem->text();

    query.prepare("DELETE FROM notes WHERE name = '"+name+"'");

    if (query.exec()) {
        delete selectedItem;
        qDebug() << name << " was deleted";
    } else {
        qDebug() << "Error deleting data:" << query.lastError().text();
    }
}

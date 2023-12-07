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
    setFixedSize(800, 650);

    statusBar = new QStatusBar(this);

    noteName = new QLineEdit(this);
    noteName->setGeometry(280, 10, 500, 50);
    noteName->setFont(QFont("SF Pro Black", 14));
    noteName->setStyleSheet( " background-color: #393939; selection-background-color: #999999; selection-color: #ffffff; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #393939; alternate-background-color: #303030;" );
    noteName->setPlaceholderText("Title");

    noteEdit = new QTextEdit(this);
    noteEdit->setGeometry(280, 80, 500, 500);
    noteEdit->setStyleSheet( " background-color: #393939; selection-background-color: #999999; selection-color: #ffffff; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #393939; alternate-background-color: #303030;" );
    noteEdit->setFont(QFont("SF Pro Black", 11));
    noteEdit->setPlaceholderText("Note");

    notesList = new QListWidget(this);
    notesList->setGeometry(20, 10, 240, 570);
    notesList->setStyleSheet( " background-color: #393939; selection-background-color: #999999; selection-color: #ffffff; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #393939; alternate-background-color: #303030;" );
    notesList->setFont(QFont("SF Pro Black", 12));
    connect(notesList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(doubleClick(QListWidgetItem*)));

    saveButton = new QPushButton("SAVE", this);
    saveButton->setGeometry(480, 590, 300, 40);
    saveButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #444444; alternate-background-color: #303030;" );
    saveButton->setFont(QFont("SF Pro Black", 10));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveNotes()));

    backButton = new QPushButton("BACK", this);
    backButton->setGeometry(20, 590, 240, 40);
    backButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #444444; alternate-background-color: #303030;" );
    backButton->setFont(QFont("SF Pro Black", 10));
    connect(backButton, SIGNAL(clicked()), this, SLOT(toMainWindow()));

    removeButton = new QPushButton("REMOVE", this);
    removeButton->setGeometry(280, 590, 185, 40);
    removeButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #444444; alternate-background-color: #303030;" );
    removeButton->setFont(QFont("SF Pro Black", 10));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeNote()));

    setStatusBar(statusBar);

    query.exec("SELECT * FROM notes");
    while (query.next()) {
        QString name = query.value("name").toString();
//        QString text = query.value("text").toString();

//        QString note = name + text;

//        QListWidgetItem *item = new QListWidgetItem(note);
        QListWidgetItem *item = new QListWidgetItem(name);
        notesList->addItem(item);

        qDebug() << name << " was loaded";
        statusBar->showMessage("All notes was loaded");
    }
}


Notes::~Notes() {
    delete ui;
}

void Notes::toMainWindow() {
    QString text = noteEdit->toPlainText();
    if(text.isEmpty()) {
        close();
        MainWindow *mainWindow = new MainWindow(this);
        mainWindow->setWindowIcon(QIcon("://home.svg"));
        mainWindow->show();
    }
    else {
        qDebug() << "Save the note first.";
        statusBar->showMessage("Save the note first.");
    }
}

void Notes::saveNotes() {
    QSqlQuery query;
    QString text = noteEdit->toPlainText().toUtf8();
    QString title = noteName->text().toUtf8();
    QString note = title + text;


    if(!text.isEmpty()) {
        if(query.exec("SELECT id FROM notes WHERE name = '"+title+"'")) {
            if (query.next()) {
                int id = query.value("id").toInt();
                if(query.exec("UPDATE notes SET text = '"+text+"' WHERE id = "+id+"")) {
                    qDebug() << title << " was updates";
                    statusBar->showMessage(title + " was updated");

                    noteEdit->clear();
                    noteName->clear();
                }
                else {
                    qDebug() << query.lastError();
                    statusBar->showMessage(query.lastError().text());
                }
            }
            else {
                if(query.exec("INSERT INTO notes (name, text) VALUES('"+title+"', '"+text+"');")) {
                    noteEdit->clear();
                    noteName->clear();

                    QListWidgetItem *item = new QListWidgetItem(title);
                    notesList->addItem(item);

                    qDebug() << title << " was saved";
                    statusBar->showMessage(title + " was saved");
                }
                else {
                    qDebug() << query.lastError();
                    statusBar->showMessage(query.lastError().text());
                }
            }
        }
        else {
            qDebug() << query.lastError().text();
            statusBar->showMessage(query.lastError().text());
        }
    }
    else {
        qDebug() << "Note is empty";
        statusBar->showMessage("Note is empty");
    }
}

void Notes::doubleClick(QListWidgetItem *item) {
    QString text = noteEdit->toPlainText();
    if(text.isEmpty()) {
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
                statusBar->showMessage(name + " was opened");
                delete notesList->takeItem(notesList->row(item));
            }
        }
        else {
            qDebug() << "Error moving data: " << query.lastError().text();
            statusBar->showMessage(query.lastError().text());
        }

/*
        query.prepare("DELETE FROM notes WHERE name = '"+name+"'");

        if (query.exec()) {
            delete notesList->takeItem(notesList->row(item));
            qDebug() << name << " was opened";
            statusBar->showMessage(name + " was opened");
        } else {
            qDebug() << "Error moving data: " << query.lastError().text();
            statusBar->showMessage(query.lastError().text());
        }
*/
    }
    else {
        qDebug() << "Previous changes were not saved. save them and try again.";
        statusBar->showMessage("Previous changes were not saved. save them and try again.");
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
        statusBar->showMessage(name + " was deleted");
    } else {
        qDebug() << "Error deleting data:" << query.lastError().text();
        statusBar->showMessage(query.lastError().text());
    }
}

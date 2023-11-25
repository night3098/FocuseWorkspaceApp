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
        qDebug() << "Невозможно создать таблицу notes, либо она уже создана";
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
    noteName->setFont(QFont("SF Pro Black", 15));
    noteName->setStyleSheet( " background-color: #393939; selection-background-color: #999999; selection-color: #ffffff; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #393939; alternate-background-color: #303030;" );
    noteName->setPlaceholderText("Title");

    noteEdit = new QTextEdit(this);
    noteEdit->setGeometry(280, 150, 500, 500);
    noteEdit->setStyleSheet( " background-color: #393939; selection-background-color: #999999; selection-color: #ffffff; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #393939; alternate-background-color: #303030;" );
    noteEdit->setFont(QFont("SF Pro Black", 12));
    noteEdit->setPlaceholderText("Note");

    notesList = new QListWidget(this);
    notesList->setGeometry(20, 80, 240, 570);
    notesList->setStyleSheet( " background-color: #393939; selection-background-color: #999999; selection-color: #ffffff; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #393939; alternate-background-color: #303030;" );
    notesList->setFont(QFont("SF Pro Black", 7));
    connect(notesList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(doubleClick(QListWidgetItem*)));

    saveButton = new QPushButton("SAVE", this);
    saveButton->setGeometry(605, 665, 175, 40);
    saveButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #444444; alternate-background-color: #303030;" );
    saveButton->setFont(QFont("SF Pro Black", 10));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveNotes()));

    backButton = new QPushButton("BACK", this);
    backButton->setGeometry(20, 665, 365, 40);
    backButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #444444; alternate-background-color: #303030;" );
    backButton->setFont(QFont("SF Pro Black", 10));
    connect(backButton, SIGNAL(clicked()), this, SLOT(toMainWindow()));

    removeButton = new QPushButton("REMOVE", this);
    removeButton->setGeometry(410, 665, 175, 40);
    removeButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-style: solid; border-radius: 10px; border-color: #444444; alternate-background-color: #303030;" );
    removeButton->setFont(QFont("SF Pro Black", 10));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeNote()));
}


Notes::~Notes() {
    delete ui;
}

void Notes::toMainWindow() {
    close();
    MainWindow *mainWindow = new MainWindow(this);
    mainWindow->setWindowIcon(QIcon("../images/home.svg"));
    mainWindow->show();
}

void Notes::saveNotes() {
    QString text = noteEdit->toPlainText();
    if(!text.isEmpty()) {
        QSqlQuery query;

        QString title = noteName->text();

        qDebug() << title;
        QString note = title + " : " + text;
        notesList->addItem(note);

        QString exec = "INSERT INTO notes (name, text) VALUES('"+title+"', '"+text+"');";

        if(!query.exec(exec)) {
            qDebug() << "Невозможно провести данную операцию, либо запись уже внесена";
            qDebug() << query.lastError();
        }
        else {
            qDebug() << "Запись добавлена";
        }

        noteEdit->clear();
        noteName->clear();
    }
    else {
        qDebug() << "Note is empty";
    }
}

void Notes::doubleClick(QListWidgetItem *item) {
    QString note = item->text();
    QStringList parts = note.split(": ");

    if (parts.size() == 2) {
        noteName->setText(parts[0]);
        noteEdit->setPlainText(parts[1]);

        delete notesList->takeItem(notesList->row(item));
    }
}


void Notes::removeNote() {
    QSqlQuery query;
    //qDeleteAll(notesList->selectedItems());
    if(!query.exec("SELECT * FROM notes;")) {
        qDebug() << query.lastError();
    }
    else{
        qDebug() << "OK";
    }
}

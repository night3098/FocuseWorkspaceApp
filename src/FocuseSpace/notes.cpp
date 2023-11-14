#include "notes.h"
#include "ui_notes.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QMainWindow>

Notes::Notes(QMainWindow *parent) :
    QMainWindow(parent)
    ,ui(new Ui::Notes) {
    ui->setupUi(this);
}

Notes::~Notes() {
    delete ui;
}



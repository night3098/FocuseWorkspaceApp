#include "pomodoro.h"
#include "ui_pomodoro.h"
#include <QDialog>
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include "mainwindow.h"
#include "ui_mainwindow.h"

Pomodoro::Pomodoro(QMainWindow *parent) :
    QMainWindow(parent) {
        
    setWindowTitle("~ pomodoro ~");
    setFixedSize(250, 225);

    titleLabel = new QLabel("POMODORO", this);
    titleLabel->setGeometry(0, 20, 250, 50);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(QFont("SF Pro Black", 30));
    titleLabel->setStyleSheet( " color: #ffffff; " );

    progressBar = new QProgressBar(this);
    progressBar->setGeometry(10, 85, 230, 40);
    progressBar->setStyleSheet( "color: #ffffff; selection-color: #000000; gridline-color: #303030; background-color: #303030; selection-background-color: #ffffff;" );
    progressBar->setFont(QFont("SF Pro Black", 12));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));

    startButton = new QPushButton("START", this);
    startButton->setGeometry(10, 130, 110, 40);
    startButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-radius: 10px; border-style: solid; border-color: #444444; alternate-background-color: #303030;" );
    startButton->setFont(QFont("SF Pro Black", 12));
    connect(startButton, SIGNAL(clicked()), this, SLOT(startPomodoro()));

    stopButton = new QPushButton("STOP", this);
    stopButton->setGeometry(130, 130, 110, 40);
    stopButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-radius: 10px; border-style: solid; border-color: #444444; alternate-background-color: #303030;" );
    stopButton->setFont(QFont("SF Pro Black", 12));
    connect(stopButton, SIGNAL(clicked()), timer, SLOT(stop()));

    changeButton = new QPushButton("CHANGE", this);
    changeButton->setGeometry(10, 175, 110, 40);
    changeButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-radius: 10px; border-style: solid; border-color: #444444; alternate-background-color: #303030;" );
    changeButton->setFont(QFont("SF Pro Black", 12));
    connect(changeButton, SIGNAL(clicked()), this, SLOT(change()));

    backButton = new QPushButton("BACK", this);
    backButton->setGeometry(130, 175, 110, 40);
    backButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-radius: 10px; border-style: solid; border-color: #444444; alternate-background-color: #303030;" );
    backButton->setFont(QFont("SF Pro Black", 12));
    connect(backButton, SIGNAL(clicked()), this, SLOT(toMainWindow()));

    timeLeft = 25 * 60;
    isPomodoro = true;
    isBreak = false;
}

Pomodoro::~Pomodoro() {
    delete ui;
}


void Pomodoro::startPomodoro() {
    isBreak = false;
    timeLeft = 25 * 60;
    progressBar->setRange(0, timeLeft);
    progressBar->setValue(timeLeft);
    titleLabel->setFont(QFont("SF Pro Black", 30));
    titleLabel->setText("POMODORO");
    titleLabel->setStyleSheet( " color: #ff3438; " );
    progressBar->setStyleSheet( "color: #ff3438; selection-color: #000000; gridline-color: #303030; background-color: #303030; selection-background-color: #ff3438;" );
    startButton->setText("RESTART");
    timer->start(1000);
}

void Pomodoro::startBreak() {
    isBreak = true;
    timeLeft = 5 * 60;
    progressBar->setRange(0, timeLeft);
    progressBar->setValue(timeLeft);
    titleLabel->setFont(QFont("SF Pro Black", 30));
    titleLabel->setText("BREAK");
    titleLabel->setStyleSheet( " color: #5fe053; " );
    progressBar->setStyleSheet( "color: #5fe053; selection-color: #000000; gridline-color: #303030; background-color: #303030; selection-background-color: #5fe053;" );
    setWindowTitle("~ break ~");
    timer->start(1000);
} 

void Pomodoro::updateTimer() {
    if (timeLeft > 0) {
        timeLeft--;
        progressBar->setValue(timeLeft);

        int minutes = timeLeft / 60;
        int seconds = timeLeft % 60;

        QString timeString = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
        titleLabel->setText(timeString);
        titleLabel->setFont(QFont("SF Pro Black", 50));
    } else {
        timer->stop();
        if (isPomodoro) {
            isPomodoro = false;
            startBreak();
        } else {
            isPomodoro = true;
            titleLabel->setText("POMODORO");
            titleLabel->setFont(QFont("SF Pro Black", 30));
        }
    }
}

void Pomodoro::stop() {
    setWindowTitle("pomodoro");
    timeLeft=0;
    progressBar->setValue(0);
    isPomodoro = false;
    isBreak = false;
    titleLabel->setFont(QFont("SF Pro Black", 30));
    titleLabel->setText("POMODORO");
    titleLabel->setGeometry(0, 20, 250, 50);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet( " color: #ffffff; " );
    timer->start(0);
}

void Pomodoro::change() {
    if(isBreak) {
        startPomodoro();
    }
    else {
        startBreak();
    }
}

void Pomodoro::toMainWindow() {
    close();
    /*
    MainWindow *mainWindow = new MainWindow(this);
    mainWindow->setWindowIcon(QIcon("images/home.svg"));
    mainWindow->show();
    */
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include "notes.h"
#include "pomodoro.h"
#include "tasks.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QMainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();

private slots:
    void openTasksWin();
    void openNotesWin();
    void openPomodoroWin();

private:
    QLabel *titleMain;
    QPushButton *openTasks;
    QPushButton *openNotes;
    QPushButton *openTimer;
    QPushButton *closeWindow;
    Tasks *tasks_window;
    Notes *notes_window;
    Pomodoro *pomodoro_window;

};
#endif // MAINWINDOW_H

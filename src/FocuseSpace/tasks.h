#ifndef TASKS_H
#define TASKS_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QLineEdit>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStatusBar>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class Tasks; }
QT_END_NAMESPACE

class Tasks : public QMainWindow
{
    Q_OBJECT

public:
    explicit Tasks(QMainWindow *parent = nullptr);
    ~Tasks();

private slots:
    void addTask();
    void toMainWindow();
    void removeTask();
    void removeDone();
    void moveToTasks(QListWidgetItem*);
    void moveToDone(QListWidgetItem*);

private:
    QStatusBar *statusBar;
    QListWidget *taskList;
    QListWidget *doneList;
    QLabel *doneLabel;
    QLabel *taskLabel;
    QLineEdit *taskInput;
    QSqlQuery query;

    QPushButton *removeButton;
    QPushButton *clearTask;
    QPushButton *backButton;

    Ui::Tasks *ui;
    Tasks *tasks;
};

#endif

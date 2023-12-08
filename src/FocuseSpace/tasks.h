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

class Tasks : public QMainWindow {
    Q_OBJECT

public:
    Tasks(QMainWindow *parent = nullptr);

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
};

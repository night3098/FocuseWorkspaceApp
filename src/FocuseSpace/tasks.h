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
    void moveTask();
    void toMainWindow();
    void removeTask();
    void removeDone();

private:
    QStatusBar *statusBar;
    QListWidget *taskList;
    QListWidget *doneList;
    QLabel *doneLabel;
    QLabel *taskLabel;
    QLineEdit *taskInput;
    QSqlQuery query;

    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *clearTask;
    QPushButton *backButton;
};

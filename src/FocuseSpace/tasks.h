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
    QListWidget *taskList;
    QListWidget *doneList;
    QLabel *winTitle;
    QLineEdit *taskInput;
    QSqlQuery query;

    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *clearTask;
    QPushButton *backButton;
};

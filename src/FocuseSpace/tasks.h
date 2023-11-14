#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QLineEdit>

class Tasks : public QMainWindow {
    Q_OBJECT

public:
    Tasks(QMainWindow *parent = nullptr);

private slots:
    void addTask();
    void removeTask();\
    void toMainWindow();

private:
    QLabel *winTitle;
    QListWidget *taskList;
    QLineEdit *taskInput;
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *backButton;
};
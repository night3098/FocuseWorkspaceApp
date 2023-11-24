#ifndef NOTES_H
#define NOTES_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>
#include <QSqlDatabase>
#include <QSqlError>

QT_BEGIN_NAMESPACE
namespace Ui { class Notes; }
QT_END_NAMESPACE

class Notes : public QMainWindow
{
    Q_OBJECT

public:
    explicit Notes(QMainWindow *parent = nullptr);
    ~Notes();

private slots:
    void toMainWindow();
    void saveNotes();
    void removeNote();
    void doubleClick(QListWidgetItem*);

private:
    QLabel *title;
    QTextEdit *noteEdit;
    QListWidget *notesList;
    QLineEdit *noteName;

    QPushButton *saveButton;
    QPushButton *backButton;
    QPushButton *removeButton;

    Ui::Notes *ui;
    Notes *notes;
};

#endif // WINDOW2_H

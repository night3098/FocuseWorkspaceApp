#ifndef NOTES_H
#define NOTES_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

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
    
private:
    QLabel *title;
    QTextEdit *noteEdit;

    QPushButton *saveButton;
    QPushButton *editButton;
    QPushButton *backButton;
    QPushButton *removeButton;

    Ui::Notes *ui;
    Notes *notes;
};

#endif // WINDOW2_H

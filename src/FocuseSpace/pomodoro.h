#ifndef POMODORO_H
#define POMODORO_H

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class Pomodoro; }
QT_END_NAMESPACE

class Pomodoro : public QMainWindow
{
    Q_OBJECT

public:
    explicit Pomodoro(QMainWindow *parent = nullptr);
    ~Pomodoro();

private slots:
    void toMainWindow();
    void startPomodoro();
    void updateTimer();
    void startBreak();
    void stop();
    void change();

private:
    QLabel *titleLabel;
    QProgressBar *progressBar;
    QTimer *timer;
    QMessageBox *notificationwork;
    QMessageBox *notificationpause;
    int timeLeft;
    bool isPomodoro;
    bool isBreak;
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *changeButton;
    QPushButton *backButton;
    
    Ui::Pomodoro *ui;
    Pomodoro *pomodoro;
};



#endif // POMODORO_H

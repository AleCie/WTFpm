#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <sstream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_PauseStart_clicked();
    void on_WTF_clicked();
    void on_Reset_clicked();

    void timerUpdate();

private:
    Ui::MainWindow *ui;

    void calculateWTFpm();
    void displayWTFpm();

    void calculateWTFps();
    void displayWTFps();

    const double scale = 0.01;

    QTimer *timer;

    int elapsedSeconds;
    int elapsedMinutes;
    double wtfps;
    double wtfpm;

    std::stringstream timer_ss;
    std::stringstream statusbar_ss;

    int wtfCount;
    int wtfCountThisMinute;
};

#endif // MAINWINDOW_H

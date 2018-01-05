#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QSizeGrip"
#include "QDebug"

#include <sstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(300, 110);
    setWindowFlags(Qt::WindowStaysOnTopHint);

    this->statusBar()->showMessage("Total WTF:");

    wtfpm = 0;
    wtfps = 0;
    elapsedSeconds = 0;
    elapsedMinutes = 0;
    wtfCount = 0;
    wtfCountThisMinute = 0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));

    ui->PauseStart->setText("Start");
    ui->MainCounter->setText("(minutes)");
    ui->SCounter->setText("(seconds)");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PauseStart_clicked()
{
    if(timer->isActive() == true)
    {
        timer->stop();
        ui->PauseStart->setText("Start");
    }else
    {
        timer->start(1000);
        ui->PauseStart->setText("Pause");
    }
}

void MainWindow::timerUpdate()
{
    elapsedSeconds++;
    if(elapsedSeconds == 61)
    {
        elapsedMinutes ++;
        elapsedSeconds = 0;

        calculateWTFpm();
        displayWTFpm();
    }

    calculateWTFps();
    displayWTFps();
}

void MainWindow::on_WTF_clicked()
{
    if(timer->isActive() == true)
    {
        wtfCount++;
        wtfCountThisMinute++;

        calculateWTFps();
        displayWTFps();

        statusbar_ss.str("");
        statusbar_ss << "Total WTF: " << wtfCount;

        this->statusBar()->showMessage(statusbar_ss.str().c_str());
    }
}

void MainWindow::calculateWTFpm()
{
    double wtfpmDivider = elapsedMinutes;
    if(wtfpmDivider > 0)
    {
        wtfpm = wtfCount / wtfpmDivider;
    }

    wtfpm = floor(wtfpm / scale + 0.5) * scale;
}

void MainWindow::displayWTFpm()
{
    timer_ss.str("");
    timer_ss << wtfpm << " wtf / ";
    timer_ss << elapsedMinutes << " (m)";
    ui->MainCounter->setText(timer_ss.str().c_str());
}

void MainWindow::calculateWTFps()
{
    double wtfpsDivider = elapsedSeconds + elapsedMinutes * 60;
    if(wtfpsDivider > 0)
    {
        wtfps = wtfCount / wtfpsDivider;
    }

    wtfps = floor(wtfps / scale + 0.5) * scale;
}

void MainWindow::displayWTFps()
{
    timer_ss.str("");
    timer_ss << wtfps << " wtf / ";
    timer_ss << (elapsedMinutes * 60 + elapsedSeconds) << " (s)";
    ui->SCounter->setText(timer_ss.str().c_str());
}

void MainWindow::on_Reset_clicked()
{
    timer->stop();

    wtfpm = 0;
    wtfps = 0;
    elapsedSeconds = 0;
    elapsedMinutes = 0;
    wtfCount = 0;
    wtfCountThisMinute = 0;

    ui->PauseStart->setText("Start");
    ui->MainCounter->setText("(minutes)");
    ui->SCounter->setText("(seconds)");

    this->statusBar()->showMessage("Total WTF:");
}

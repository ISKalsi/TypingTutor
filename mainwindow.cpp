#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "help.h"
#include "practice.h"
#include "play.h"
#include "highscore.h"
#include<QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    MainWindow::showMaximized();
    ui->setupUi(this);
    setWindowTitle("Typing Tutor");
    player=new QMediaPlayer(this);
    QPixmap pix(":/imgs/pictures/main4.png");
    ui->label->setPixmap(pix);

    QDir dir("highscore");
    if(!dir.exists())
        dir.mkpath(".");

    QFile f1("highscore/easy_highscore.txt");
    QFile f2("highscore/medium_highscore.txt");
    QFile f3("highscore/hard_highscore.txt");

    f1.open(QFile::ReadWrite);
    f2.open(QFile::ReadWrite);
    f3.open(QFile::ReadWrite);

    f1.close();
    f2.close();
    f3.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    play play;
    play.setModal(true);
    play.exec();
}


void MainWindow::on_pushButton_3_clicked()
{
    help help;
    help.setModal(true);
    help.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    practice practice;
    practice.setModal(true);
    practice.exec();
}

void MainWindow::on_pushButton_4_clicked()
{
    close();
}



/*void MainWindow::on_radioButton_clicked(bool n)
{
    if(n==true){
        player->setMedia(QUrl::fromLocalFile("C:/Users/Samip/Desktop/nem.mp3"));
        player->play();
    }
    if(n==false){
        player->stop();
    }

}*/

void MainWindow::on_pushButton_5_clicked()
{
    highscore highscore;
    highscore.setModal(true);
    highscore.exec();

}

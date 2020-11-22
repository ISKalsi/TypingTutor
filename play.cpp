#include "play.h"
#include "ui_play.h"
#include "easy.h"
#include "normal.h"
#include "hard.h"
#include"QPixmap"

play::play(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::play)
{
    ui->setupUi(this);
    setWindowTitle("PLAY");
    QPixmap pix1(":/imgs/pictures/easy_final");
    ui->label->setPixmap(pix1);
    QPixmap pix2(":/imgs/pictures/medium_final");
    ui->label_2->setPixmap(pix2);
    QPixmap pix3(":/imgs/pictures/hard_final");
    ui->label_3->setPixmap(pix3);


}

play::~play()
{
    delete ui;
}

void play::on_pushButton_easy_clicked()
{
    easy easy;
    easy.setModal(true);
    easy.exec();

}

void play::on_pushButton_normal_clicked()
{
    normal normal;
    normal.setModal(true);
    normal.exec();
}

void play::on_pushButton_hard_clicked()
{
    hard hard;
    hard.setModal(true);
    hard.exec();

}

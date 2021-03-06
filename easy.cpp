#include "easy.h"
#include "ui_easy.h"
#include"QFile"
#include "QTextStream"
#include"QMessageBox"
#include"QList"
#include"QTime"
#include "stdlib.h"
#include"QApplication"
#include<QKeyEvent>


easy::easy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::easy)
    {
        ui->setupUi(this);
        setWindowTitle("EASY");
        correct = new QMediaPlayer(this);
        correct->setMedia(QUrl::fromLocalFile(":/music/music/correct.mp3"));
        incorrect = new QMediaPlayer(this);
        incorrect->setMedia(QUrl::fromLocalFile(":/music/music/wrong.mp3"));
        buzzer = new QMediaPlayer(this);
        buzzer->setMedia(QUrl::fromLocalFile(":/music/music/buzzer.mp3"));
        wow = new QMediaPlayer(this);
        wow->setMedia(QUrl::fromLocalFile(":/music/music/wow.mp3"));
        QPixmap pix1(":/imgs/pictures/easy");
        ui->label->setPixmap(pix1);
        connect(ui->textBrowser,SIGNAL(textChanged()),this,SLOT(stopwatch()));
    }

easy::~easy()
{
    delete ui;
}

void easy::keyPressEvent(QKeyEvent *event){
    //key press event for Exit
    if(event->key() == Qt::Key_Escape){
        QMessageBox::StandardButton reply1= QMessageBox::question(this, "EXIT", "Do you sure want to exit?");

       if(reply1 == QMessageBox::Yes){
           s = 12;
           i = 100;
           // score=0;
           highscore();
           close();
       }
    }




    //key press event for Start
    if(event->key() == Qt::Key_Control){
       if(start_value == 0){
           ui->lineEdit->clear();
           QFile file(":/data/data/Easy.txt");
           if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
               QMessageBox::warning(this,"Error","File not open");

            QTextStream  in(&file);
            while(!in.atEnd()){
                line = in.readLine();
                list.append(line);
            }
            start_value=1;

            for(i=0; i<50; i++){
                if(s != 5){
                    srand(time(NULL));
                    j=1 + rand() % (225);
                    s = 0;
                    ui->textBrowser->setPlainText(list[j]);
                }
            }

            file.close();
         }
       else if(start_value==1){
           QMessageBox::information(this,"PAUSED","Press OK to Resume");
       }
    }
}


void easy::stopwatch(){
    while(s < 6){
        ui->stopwatch->setNum(s);
        if(s == 5){
            buzzer->play();
            life = life - 1;
            life_cont = 0;
            ui->lineEdit->clear();
            if(life == 0){


                    highscore();


                ui->life->setNum(0);
                QMessageBox::StandardButton reply= QMessageBox::question(this, "Game Over", "Game Over - Do you want to play again");

                if(reply == QMessageBox::Yes){
                     life = 3;
                     score = 0;
                     ui->life->setNum(life);
                     ui->score->setNum(score);
                     ui->lineEdit->clear();
                     j = 1 + rand() % (225);
                     s = 0;
                     ui->textBrowser->setPlainText(list[j]);
                }
                else{
                     i = 100;
                     close();
                     break;
                }


            }
            j=1+rand()%(225);
            s=0;
            ui->textBrowser->setPlainText(list[j]);

        }
        s = s + 1;
        QTime dieTime = QTime::currentTime().addSecs(1);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 500);

        ui->life->setNum(life);
    }
}

void easy::Box(){
    if(reply == QMessageBox::Yes){
          life = 3;
          score = 0;
          ui->life->setNum(life);
          ui->score->setNum(score);
          ui->lineEdit->clear();
          ui->textBrowser->clear();
    }
    else {
          s = 12;
          i = 100;
          close();
    }
}




void easy::timer(){
    QTime dieTime = QTime::currentTime().addSecs(5);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void easy::on_lineEdit_returnPressed(){

     QString str = ui->lineEdit->text();
     if(list[j] == str){
         score = score + 1;
         ui->score->setNum(score);
         correct->play();
         ui->lineEdit->clear();
         life_cont = life_cont + 1;
         if(life<3 && life_cont==10){
             life = life + 1;
             ui->life->setNum(life);
             wow->play();
             life_cont = 0;
         }
         j = 1 + rand() % (225);
         s = 0;
         ui->textBrowser->setPlainText(list[j]);


     }
     else{
         life_cont = 0;
         life = life - 1;
         incorrect->play();
         if (life > 0){
             ui->life->setNum(life);
             ui->lineEdit->clear();
             s = 0;
             j = 1 + rand() % (225);
             ui->textBrowser->setPlainText(list[j]);

         }
         else{
             ui->life->setNum(0);
             QMessageBox::StandardButton reply= QMessageBox::question(this, "Game Over", "Game Over - Do you want to play again");

            if(reply == QMessageBox::Yes){
                  life = 3;
                  score = 0;
                  ui->life->setNum(life);
                  ui->score->setNum(score);
                  ui->lineEdit->clear();
                  highscore();
                  s = 0;
                  j = 1 + rand() % (225);
                  ui->textBrowser->setPlainText(list[j]);
            }
            else {
                  s = 15;
                  i = 100;
                  highscore();
                  close();
            }
        }
    }
}
void easy::highscore(){

    QFile file1("highscore/easy_highscore.txt");
    if(!file1.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Error","File not open");}
    QTextStream in(&file1);
    while(!in.atEnd()){
       hscore = in.readAll();

    }
    file1.close();

    QFile file2("highscore/easy_highscore.txt");
    if(!file2.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Error","File not open");}
    QTextStream out(&file2);
    if(hscore.toInt()<=score){
        out<<score;
    }
    else {
        out<<hscore;
    }

    file2.flush();
    file2.close();
    s=25;

}

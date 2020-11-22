#include "practice.h"
#include "ui_practice.h"
#include "QMessageBox"
#include "QKeyEvent"
#include"QTextStream"
#include "QTime"
#include "QList"
#include "QApplication"
#include "QFile"
#include"result.h"

practice::practice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::practice)
{
    ui->setupUi(this);
    setWindowTitle("PRACTICE");
    QPixmap pix(":/imgs/pictures/practice2.png");
    ui->label->setPixmap(pix);
    connect(ui->textBrowser,SIGNAL(textChanged()),this, SLOT(stopwatch()));
}

practice::~practice()
{
    delete ui;
}

void practice::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Escape){
        QMessageBox::StandardButton reply1= QMessageBox::question(this, "EXIT", "Do you sure want to exit?");

       if(reply1 == QMessageBox::Yes){

           close();
       }
    }





    if(event->key() == Qt::Key_Control){
       if(start_v == 0){
           s=120;
           ui->remark->clear();
           ui->letters->clear();
           ui->lineEdit->clear();
           QFile file3(":/data/data/practice.txt");
           if(!file3.open(QFile::ReadOnly | QFile::Text))
               QMessageBox::warning(this,"Error","File not open");

            QTextStream  in(&file3);
            while(!in.atEnd()){
                line = in.readLine();
                list.append(line);
            }
            start_v=1;

            for(i=0; i<50; i++){
                if(s != 0){
                    srand(time(NULL));
                    j=1 + rand() % (30);
                    //s =120;
                    ui->textBrowser->setPlainText(list[j]);
                }
            }

            file3.close();
         }
       else if(start_v==1){
           QMessageBox::information(this,"PAUSED","Press OK to Resume");
       }
    }
}

void practice::stopwatch(){
    while(s>=0){
        ui->stopwatch->setNum(s);
        if(s ==0){
          ui->lineEdit->clear();
          wpm=letters/(2*5);
          ui->letters->setNum(wpm);
           ui->lineEdit->setText("Press CTRL to practice again!!");
           if(wpm>65){
               ui->remark->setText("EXCELLENT!!");
           }
           else if (wpm<=65 && wpm>40) {
               ui->remark->setText("Above Average");
           }
           else if(wpm<=40 && wpm>30){
               ui->remark->setText("Average");
           }
           else if(wpm<=30 && wpm >20){
               ui->remark->setText("Work Hard");
           }
           else {
               ui->remark->setText("Poor");
           }

           start_v=0;



            break;


        }
          s = s - 1;
          QTime dieTime = QTime::currentTime().addSecs(1);
          while (QTime::currentTime() < dieTime)
              QCoreApplication::processEvents(QEventLoop::AllEvents, 500);

}
}

void practice::on_lineEdit_returnPressed()
{
    QString str = ui->lineEdit->text();
    if(list[j] == str){
        letters=letters+str.length();

    }
    ui->lineEdit->clear();
    j = 1 + rand() % (30);
    ui->textBrowser->setPlainText(list[j]);
}

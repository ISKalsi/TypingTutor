#include "practice.h"
#include "ui_practice.h"
#include "QMessageBox"
#include "QKeyEvent"
#include "QTextStream"
#include "QTime"
#include "QList"
#include "QApplication"
#include "QFile"
#include "result.h"
#include <QDebug>

practice::practice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::practice)
{
    ui->setupUi(this);
    setWindowTitle("PRACTICE");
    QPixmap pix(":/imgs/pictures/practice2.png");
    ui->label->setPixmap(pix);
    ui->lineEdit->setPlaceholderText("Press CTRL to start");

    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(checkChange(QString)));

    // importing all the words from the text file in a list
    QFile file(":/data/data/practice.txt");
    if(!file.open(QFile::ReadOnly | QFile::Text))
        QMessageBox::warning(this,"Error","File not open");

    QTextStream  in(&file);
    QString tempWord;

    while(!in.atEnd()){
        in >> tempWord;
        wordlist.append(tempWord);
    }

    file.close();

    total_words = wordlist.size();
    reset(true);
}

practice::~practice()
{
    delete ui;
}

void practice::reset(bool init=false) {
    srand(time(0));
    QString line;

    if(init) {
        words_on_screen.push_front("x");     //for color change purposes

        for(int i = 1; i < WORDS_ON_SCREEN; i++) {
            words_on_screen.push_back(wordlist[rand() % total_words]);
            line += words_on_screen[i] + " ";
        }
    } else {
        changeColor(words_on_screen[0], word_spelling::clear);

        for(int i = 0; i < WORDS_ON_SCREEN; i++) {
            int x = rand() % total_words;

            words_on_screen.pop_front();
            words_on_screen.push_back(wordlist[x]);

            line += wordlist[x] + " ";
        }

        words_on_screen.push_front("x");        //for color change purposes
    }

    current_word = words_on_screen[1] + " ";
    words_typed_length = correct_words = incorrect_words = incorrect_chars = currentIndex = 0;

    ui->textBrowser->setPlainText(line);
}

void practice::changeColor(QString& text, word_spelling choice) {

    switch (choice) {
        case correct:
            text = CORRECT_TAG + text;
            break;
        case wrong:
            text = WRONG_TAG + text;
            break;
        case clear:
            QString temp;
            bool flag = false;
            for(int i = 0; i < text.size(); i++) {
                if(text[i] == '>')
                    flag = true;
                else if(text[i] == '<')
                    flag = false;
                else if(flag)
                    temp += text[i];
            }

            text = flag ? temp : " ";
            return;
    }

    text += END_TAG;
}

void practice::checkChange(QString text) {
    if(practice_in_progress && !text.isEmpty()) {
        if(text.back() != ' ') {
            if(text.size() <= currentIndex) {
                currentIndex--;
            } else {
                if(current_word.size() <= currentIndex || current_word[currentIndex] != text[currentIndex])
                    ++incorrect_chars;
                currentIndex++;
            }
        } else {
            if (text != current_word) {
                incorrect_words++;
                changeColor(words_on_screen[1], word_spelling::wrong);
            } else {
                correct_words++;
                changeColor(words_on_screen[1], word_spelling::correct);
            }

            words_typed_length += text.size();

            update_screen_text();
        }
    }
}

void practice::keyPressEvent(QKeyEvent *event){
    int key = event->key();

    if(key == Qt::Key_Escape){
        QMessageBox::StandardButton reply= QMessageBox::question(this, "Paused", "Do you want to exit?");

        if(reply == QMessageBox::Yes) {
            practice_in_progress = false;
            close();
        }
    }

    if(key == Qt::Key_Control) {
        if(!practice_in_progress) {
            seconds = SECONDS;

            ui->remark->clear();
            ui->letters->clear();
            ui->lineEdit->clear();
            ui->lineEdit->setPlaceholderText("");

            practice_in_progress = true;
            stopwatch();
        }
    }
}

void practice::stopwatch(){
    for(;seconds >= 0; seconds--) {
        ui->stopwatch->setNum(seconds);

        if(!practice_in_progress)
            return;

        QTime dieTime = QTime::currentTime().addSecs(1);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 500);
    }

    practice_in_progress = false;

    calculate_result(words_typed_length, correct_words, incorrect_words, incorrect_chars, SECONDS/60.0);

    words_typed_length = correct_words = incorrect_words = incorrect_chars = currentIndex = 0;

    ui->lineEdit->clear();
    ui->letters->setNum(speed);
    ui->lineEdit->setPlaceholderText("Press CTRL to start again");

    reset();

    if(speed>65){
        ui->remark->setText("EXCELLENT!!");
    }
    else if (speed<=65 && speed>40) {
        ui->remark->setText("Above Average");
    }
    else if(speed<=40 && speed>30){
        ui->remark->setText("Average");
    }
    else if(speed<=30 && speed >20){
        ui->remark->setText("Work Hard");
    }
    else {
        ui->remark->setText("Poor");
    }
}

void practice::update_screen_text() {
    words_on_screen.push_back(wordlist[rand() % total_words]);
    words_on_screen.pop_front();

    current_word = words_on_screen[1] + " ";
    currentIndex = 0;

    QString line;
    for(int i = 0; i < WORDS_ON_SCREEN; i++)
        line += words_on_screen[i] + " ";

    ui->textBrowser->clear();
    ui->textBrowser->setHtml(line);
    ui->lineEdit->clear();
}

void practice::calculate_result(int charTypd, int corrW, int incW, int incC, float mins)
{
    speed = corrW / mins;
    accuracy = ( (corrW / float(corrW+incW)) + ((charTypd - incC) / float(charTypd)) ) * 50.0;

    qDebug() << "==============================\n"
         << "=          Results           =\n"
         << "==============================\n\n"
         << "Characters typed: " << charTypd <<" | \033[31;1m" << incC << "\e[0m\n"
         << "Correct words: \033[32;1m" << corrW << "\e[0m\n"
         << "Incorrect words: \033[31;1m" << incW << "\e[0m\n"
         << "Accuracy: " << accuracy << "%\n"
         << "Average Speed (WPM): \033[1m\033[37;1m\033[44m" << speed << "\e[0m\n";
}

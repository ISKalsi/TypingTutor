#ifndef PRACTICE_H
#define PRACTICE_H

#include <QDialog>
#include "QList"

#define WORDS_ON_SCREEN 30
#define SECONDS 10

#define CORRECT_TAG "<font color=\"Lime\">"
#define WRONG_TAG "<font color=\"#ff6347\">"
#define END_TAG "</font>"

namespace Ui {
class practice;
}

enum word_spelling {
    correct,
    wrong,
    clear
};

class practice : public QDialog
{
    Q_OBJECT

public:
    explicit practice(QWidget *parent = nullptr);
    ~practice();

private slots:
    void stopwatch();
    void checkChange(QString);

private:
    Ui::practice *ui;

    void keyPressEvent(QKeyEvent *event);
    void update_screen_text();
    void changeColor(QString&, word_spelling);
    void reset(bool);
    void calculate_result(int, int, int, int, float);

    int seconds;

    int words_typed_length, correct_words, incorrect_words, incorrect_chars;
    QString current_word;
    int currentIndex;

    QList<QString> wordlist;
    int total_words;
    QList<QString> words_on_screen;

    bool practice_in_progress = false;

    int speed;
    float accuracy;

};

#endif // PRACTICE_H

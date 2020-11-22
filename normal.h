#ifndef NORMAL_H
#define NORMAL_H

#include <QDialog>
#include<QMediaPlayer>
#include<QFile>
#include<QMessageBox>

namespace Ui {
class normal;
}

class normal : public QDialog
{
    Q_OBJECT

public:
    explicit normal(QWidget *parent = nullptr);
    ~normal();

private slots:
    void timer();
    void on_lineEdit_returnPressed();
    void stopwatch();
    void Box();
    void highscore();

private:
    Ui::normal *ui;
    QFile file;
    QString line;
    QList<QString> list;
    int i = 0;
    int j;
    QMediaPlayer* correct;
    QMediaPlayer* incorrect;
    QMediaPlayer* wow;
    QMediaPlayer* buzzer;
    int score = 0;
    int life = 3;
    int s = 1;
    QMessageBox::StandardButton reply;
    int ans;
    QMessageBox msgBox;
    void keyPressEvent(QKeyEvent *event);
    int start_value = 0;
    int life_cont;
    QString hscore;
};

#endif // NORMAL_H

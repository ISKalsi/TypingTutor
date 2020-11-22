#ifndef PRACTICE_H
#define PRACTICE_H

#include <QDialog>
#include"QList"

namespace Ui {
class practice;
}

class practice : public QDialog
{
    Q_OBJECT

public:
    explicit practice(QWidget *parent = nullptr);
    ~practice();

private slots:
    void stopwatch();

    void on_lineEdit_returnPressed();

private:
    Ui::practice *ui;
    void keyPressEvent(QKeyEvent *event);
    int s=120,i,start_v=0,j;
    QString line;
     QList<QString> list;
     int letters=0;
     double wpm;

};

#endif // PRACTICE_H

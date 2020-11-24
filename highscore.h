#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <QDialog>
#include "QFile"

namespace Ui {
class highscore;
}

class highscore : public QDialog
{
    Q_OBJECT

public:
    explicit highscore(QWidget *parent = nullptr);
    ~highscore();

private slots:
    void on_tabWidget_tabBarClicked(int index );

private:
    Ui::highscore *ui;
    QFile file;
    QString e_hscore,m_hscore,h_hscore;
};

#endif // HIGHSCORE_H

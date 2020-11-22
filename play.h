#ifndef PLAY_H
#define PLAY_H

#include <QDialog>

namespace Ui {
class play;
}

class play : public QDialog
{
    Q_OBJECT

public:
    explicit play(QWidget *parent = nullptr);
    ~play();

private slots:
    void on_pushButton_easy_clicked();

    void on_pushButton_normal_clicked();

    void on_pushButton_hard_clicked();

private:
    Ui::play *ui;
};

#endif // PLAY_H

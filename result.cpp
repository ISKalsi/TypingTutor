#include "result.h"
#include "ui_result.h"

result::result(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::result)
{
    setWindowTitle("Result");
    ui->setupUi(this);
    //connect(this,SIGNAL(windowTitleChanged()),ui->label,SLOT(setResult()));

}

result::~result()
{
    delete ui;
}

void result::setResult()
{
    QString speed;
    ui->textBrowser->setPlainText(speed.setNum(wpm));
}


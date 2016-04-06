#include "QtWithoutForm.h"
#include <cstdio>

QtWithoutForm::QtWithoutForm(QWidget *parent)
{
    resize(600, 600);
    button = new QPushButton("&Download", this);
    button->setGeometry(10, 10, 90, 30);

}

void QtWithoutForm::resizeEvent(QResizeEvent *risize) {
    //int wid, hei;
    int wid = risize->size().width();
    int hei = risize->size().height();
    button->setGeometry(wid / 2, hei / 2, 80, 20);
    printf("qt without form resize. \n");
}


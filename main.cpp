#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    //w.setBackgroundRole(QPixmap("Law.png"));
    w.setWindowIcon(QPixmap(":/images/Lancifolium.png"));
    w.setWindowTitle(QString("Lancifolium Formula"));
    //w.set
    w.show();

    return a.exec();
}

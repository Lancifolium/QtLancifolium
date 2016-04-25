#include "QtLancifolium/QtLancifolium.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtLancifolium w;
    w.show();

    return a.exec();
}

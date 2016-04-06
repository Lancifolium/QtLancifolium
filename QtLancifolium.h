#ifndef QTLANCIFOLIUM_H
#define QTLANCIFOLIUM_H

#include <QMainWindow>
#include <QWidget>
#include <qpainter.h>
#include <QPixmap>
#include <QtGui>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPolygon>
#include <QRect>
#include <QPen>
#include <QFileDialog>
#include <QString>
#include <QTextBrowser>
#include <QFile>
#include <QTextStream>
#include <QPushButton>
#include <QResizeEvent>
#include "DevLancifolium.h"
#include "Formatting.h"
#include "QtWithoutForm.h"

namespace Ui {
class QtLancifolium;
}

class QtLancifolium : public QMainWindow
{
    Q_OBJECT

public:
    explicit QtLancifolium(QWidget *parent = 0);
    ~QtLancifolium();

    void moveSimpleApp(int movx, int movy);
    void drawmoveapp(); //

private:
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void resizeEvent(QResizeEvent *);

private slots:

    void on_actionRefresh_triggered();

    void on_actionOpen_File_triggered();

    void on_actionFormat_File_triggered();

    void on_actionTestOnly_triggered();

private:
    Ui::QtLancifolium *ui;

    DevLancifolium sgf; // 棋譜文件
    GnCalculate onlymov; //

    //QPainter pain;
    QBrush brushs;
    QPen pen;
    QImage img;
    QImage imgbord; // 棋盤
    QImage imgb; // 黑子
    QImage imgw; // 白子
    QImage imgcur; //

    int win_size; // 棋盤尺寸
    int win_gap; // = win_size / 20
    int win_xlb; // 棋盤左上角的橫坐標
    int win_ylb; // 棋盤左上角的縱坐標

    int player;
    int cac; // 0 起始, 1 自戰, 2 打譜。
    int curmov;
    GnNode *current;

    QPushButton *abstention; // 棄權
};

#endif // QTLANCIFOLIUM_H

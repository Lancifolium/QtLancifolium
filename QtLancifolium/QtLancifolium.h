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
#include "Lancifolium/DevLancifolium.h"
#include "Lancifolium/MovLancifolium.h"
#include "Formatting.h"
#include "QtWithoutForm.h"

#define CAC_MOV 1 /* 自戰 */
#define CAC_SIG 2 /* 打譜 */
#define CAC_EDT 3 /* 編輯 */

struct QtLancifolium : public QMainWindow {
    Q_OBJECT

public:
    QtLancifolium(QWidget *parent = 0);
    void setbuttons();
    ~QtLancifolium();

    void simplemoving(int movx, int movy); /* 簡單打譜程序 */
    void drawingbord(int bordsiz); /* 畫出盤面 */

private:
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *las);
    void wheelEvent(QWheelEvent *eve);
    void resizeEvent(QResizeEvent *resize);

private slots:
    void on_abstention();
    void on_formatting();
    void on_openfile();
    void on_refresh();

private:
    DevLancifolium sig; /* 棋譜文件 */
    MovLancifolium onlymov; /* 用以打譜 */

    /* 繪圖 */
    QBrush brushs;
    QPen pen;
    QImage imgbord; /* 棋盤 */
    QImage imgb; /* 黑子 */
    QImage imgw; /* 白子 */
    QImage imgcur; /* 當前落子 */

    int win_size; /* 棋盤尺寸 */
    int win_gap; /* = win_size / 20 */
    int win_xlb; /* 棋盤左上角的橫坐標 */
    int win_ylb; /* 棋盤左上角的縱坐標 */

    int player;
    int cac; /* 0 起始 1 自戰 2 打譜 */
    int curmov; /* 當前落子 */
    GnNode *current;

    /* 按鈕 */
    QPushButton *butt_abstention; /* 棄權 */
    QPushButton *butt_format; /* 格式化棋譜文件 */
    QPushButton *butt_openfile;
    QPushButton *butt_refresh; /* 格式化棋譜文件 */
};

#endif // QTLANCIFOLIUM_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <qpainter.h>
#include <QPixmap>
#include <QtGui>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPen>
#include <QFileDialog>
#include <QString>
#include <QTextBrowser>
#include <QFile>
#include <QTextStream>
#include "SgfLancifolium.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);
	void wheelEvent(QWheelEvent *);

	void drawcube(); // 畫魔方
	void drawbord(); // 畫棋盤
	void drawmoveApp(); //

	void moveSimpleApp(int, int);
	void moveSimpleSgf();

private slots:
	void on_Refresh_pressed();
	void on_openfile_pressed();
	void on_Next_pressed();

private:
	SgfStruct sgf;
	GnCalculate onlymov; //

	//QPainter pain;
	QBrush brushs;
	QPen pen;
    QImage img;
    QImage imgbord; // 棋盤
    QImage imgb; // 黑子
    QImage imgw; // 白子

    int player;
    int cac; // 0 起始, 1 自戰, 2 打譜。
	int curmov;
	GnNode *current;
    Ui::Widget *ui;
};

#endif // WIDGET_H

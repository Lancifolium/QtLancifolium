#ifndef FORMULA_H
#define FORMULA_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QFileDialog>
#include <QApplication>
#include <QString>
#include <QPen>
#include <QBrush>
#include <QMessageBox>
#include <QPalette>
#include <QPushButton>
#include <QResizeEvent>
#include "Lancifolium/DevLancifolium.h"

/* 先試著實現一個簡單的打譜界面再說 */
struct Formula : public QWidget {
	Q_OBJECT
public:
	Formula(QWidget *parent = 0);
	~Formula();

private:
	void paintEvent(QPaintEvent *);
	void mouseReleaseEvent(QMouseEvent *las);
	void wheelEvent(QWheelEvent *eve);

private slots:
	void on_abstention();
	void on_backroot();
	void on_prebranch();
	void on_openfile();

private:
	DevLancifolium sig; //
	GnNode *current;

	/* 繪圖 */
	QBrush brushs;
	QPen pen;
	QImage imgbord; /* 棋盤 */
	QImage imgb; /* 黑子 */
	QImage imgw; /* 白子 */
	QImage imgcur; /* 當前落子 */

	QPushButton *butt_abstention; // 棄權
	QPushButton *butt_backroot; // 收子
	QPushButton *butt_prebranch; // 上分支
	QPushButton *butt_openfile; // 打開文件
};

#endif // FORMULA_H

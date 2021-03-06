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
#include <QLineEdit>
#include <QTextBrowser>
#include <QCheckBox>
#include <QComboBox>
#include <QResizeEvent>
#include "Lancifolium/DevLancifolium.h"

#define FORM_READ 0 // 讀譜模式
#define FORM_EDIT 1 // 編輯模式

/* 先試著實現一個簡單的打譜界面再說 */
struct Formula : public QWidget {
	Q_OBJECT
public:
	Formula(QWidget *parent = 0);
	~Formula();

	void drawingbord(); // draw bord

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
	QPushButton *butt_trymoving; // 試下

	QLineEdit *show_nodename; // 顯示節點名稱
	QTextBrowser *show_comment; // 顯示評論
	QCheckBox *show_coor; // 顯示坐標
	QComboBox *show_movnumber; // 顯示手數
};

#endif // FORMULA_H

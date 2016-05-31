#include "Formula.h"

Formula::Formula(QWidget *parent) : QWidget(parent) {
	/* 加載圖片 */
	imgbord.load(":/images/bord.png");
	imgcur.load(":/images/cur_mov.png");
	imgb.load(":/images/movblack.png");
	imgw.load(":/images/movwhite.png");

	setWindowTitle("Formulary");
	setFixedSize(900, 640);

	current = NULL;

	butt_abstention = new QPushButton("Abstention", this);
	butt_abstention->setGeometry(660, 360, 72, 24);
	connect(butt_abstention, SIGNAL(clicked(bool)), this, SLOT(on_abstention()));
	butt_backroot = new QPushButton("Abstention", this);
	butt_backroot->setGeometry(660, 390, 72, 24);
	connect(butt_backroot, SIGNAL(clicked(bool)), this, SLOT(on_backroot()));
	butt_prebranch = new QPushButton("Prev Branch", this);
	butt_prebranch->setGeometry(660, 420, 72, 24);
	connect(butt_prebranch, SIGNAL(clicked(bool)), this, SLOT(on_prebranch()));
	butt_openfile = new QPushButton("Open File", this);
	butt_openfile->setGeometry(660, 450, 72, 24);
	connect(butt_openfile, SIGNAL(clicked(bool)), this, SLOT(on_openfile()));

	sig.init();
}

Formula::~Formula() {
	delete butt_abstention;
	delete butt_backroot;
	delete butt_openfile;
	delete butt_prebranch;
}

void Formula::drawingbord() {
	QPainter pain(this);

	int win_xlb = 0;
	int win_ylb = 0;
	int win_gap = 30;
	int win_size = 600;

	int tmpi, tmpj;
	pain.setPen(Qt::blue);
	pain.setBrush(Qt::blue);
	for (tmpi = 0; tmpi < 19; tmpi++) { // 畫棋盤
		pain.drawLine(win_xlb + win_gap, win_ylb + win_gap + tmpi * win_gap,
					  win_xlb + win_gap + 18 * win_gap, win_ylb + win_gap + tmpi * win_gap);
		pain.drawLine(win_xlb + win_gap + tmpi * win_gap, win_ylb + win_gap,
					  win_xlb + win_gap + tmpi * win_gap, win_ylb + win_gap + 18 * win_gap);
	}
	int dotsize = win_gap / 10;
	for (tmpi = win_gap + 3 * win_gap - dotsize; tmpi < win_size; tmpi += 6 * win_gap) { // 畫星位
		for (tmpj = win_gap + 3 * win_gap - dotsize; tmpj < win_size; tmpj += 6 * win_gap) {
			pain.drawRect(win_xlb + tmpi, win_ylb + tmpj, dotsize * 2, dotsize * 2);
		}
	}

	for (tmpi = 0; tmpi < bordsiz; tmpi++) { // 畫棋子
		for (tmpj = 0; tmpj < bordsiz; tmpj++) {
			if (onlymov.ston[tmpi][tmpj] == 1) {
				QRect target(win_xlb + tmpi * win_gap + win_gap * 11 / 20,
							 win_ylb + tmpj * win_gap + win_gap * 11 / 20,
							 win_gap * 9 / 10,
							 win_gap * 9 / 10);
				pain.drawImage(target, imgb);
			}
			else if (onlymov.ston[tmpi][tmpj] == 2) {
				QRect target(win_xlb + tmpi * win_gap + win_gap * 11 / 20,
							 win_ylb + tmpj * win_gap + win_gap * 11 / 20,
							 win_gap * 9 / 10,
							 win_gap * 9 / 10);
				pain.drawImage(target, imgw);
			}
		}
	} // finished for

	if (curmov >= 0) { // 標註當前節點
		brushs.setColor(Qt::cyan);
		pain.setBrush(brushs);
	}
}

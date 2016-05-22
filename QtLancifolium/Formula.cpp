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

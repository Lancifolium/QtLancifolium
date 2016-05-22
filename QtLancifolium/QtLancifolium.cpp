#include "QtLancifolium.h"

/* 初始和結束的函數 */
QtLancifolium::QtLancifolium(QWidget *parent) : QMainWindow(parent) {
	/* 加載圖片 */
    imgbord.load(":/images/bord.png");
    imgcur.load(":/images/cur_mov.png");
    imgb.load(":/images/movblack.png");
    imgw.load(":/images/movwhite.png");

    setWindowTitle("Lancifolium");
    setMinimumSize(490, 430);  /* 設置最小窗口大小 */
    resize(720, 660); /* 初始化的大小 */

    win_gap = 30;
    win_size = 600;
    win_xlb = 10;
    win_ylb = 20;

    player = BLACKSTONE; /* 初始黑子 */
    curmov = -1;
    current = NULL;

	butt_abstention = new QPushButton("Abstention", this);
    connect(butt_abstention, SIGNAL(clicked(bool)), this, SLOT(on_abstention()));
	butt_format = new QPushButton("Formatting", this);
    connect(butt_format, SIGNAL(clicked(bool)), this, SLOT(on_formatting()));
	butt_openfile = new QPushButton("Open File", this);
    connect(butt_openfile, SIGNAL(clicked(bool)), this, SLOT(on_openfile()));
	butt_refresh = new QPushButton("Refresh", this);
    connect(butt_refresh, SIGNAL(clicked(bool)), this, SLOT(on_refresh()));
	setbuttgeometry(); /* set geometry*/

    cac = CAC_MOV; /* 默認爲自戰模式 */
    onlymov.init(); /* init moving app */
}

void QtLancifolium::setbuttgeometry() { /* refresh buttons' geometry */
    butt_abstention->setGeometry(win_xlb + win_size / 2 - 36, win_ylb + win_size, 72, 24);
    butt_format->setGeometry(win_xlb + win_size, win_ylb + 120, 72, 24);
    butt_openfile->setGeometry(win_xlb + win_size, win_ylb + 160, 72, 24);
    butt_refresh->setGeometry(win_xlb + win_size, win_ylb + 200, 72, 24);
}

QtLancifolium::~QtLancifolium() {
    delete butt_abstention;
    delete butt_format;
    delete butt_openfile;
    delete butt_refresh;
}

/* 繪圖程序 */
void QtLancifolium::drawingbord(int bordsiz) {
	QPainter pain(this);

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

	//pain.setRenderHint(QPainter::Antialiasing, true); // 使得邊緣柔和

    for (tmpi = 0; tmpi < bordsiz; tmpi++) {
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

    if (curmov >= 0) {
		brushs.setColor(Qt::cyan);
		pain.setBrush(brushs);


	}
}

/* system events */
void QtLancifolium::paintEvent(QPaintEvent *) {
    QPainter pain(this);
    QRect target(win_xlb, win_ylb, win_size, win_size);
    pain.drawImage(target, imgbord); // 棋盤
    brushs.setStyle(Qt::SolidPattern); // 填充模式

    switch (cac) {
    case CAC_MOV:
		drawingbord(19);
		break;
    case CAC_SIG:
		drawingbord(19);
		break;
    default: break;
	}
} // paintEvent

void QtLancifolium::mouseReleaseEvent(QMouseEvent *las) {
    switch (cac) {
	case CAC_MOV: /* 自戰 */
		simplemoving(las->x(), las->y());
		break;
	case CAC_SIG: /* 簡單讀譜 */
		if (onlymov.configDropStone(current->stoneProp, current->mov)) update();
		break;
    default: break;
	}
}

void QtLancifolium::wheelEvent(QWheelEvent *eve) { /* 滾動鼠標事件 */
    int numDegrees = eve->delta();
    switch (cac) {
    case CAC_MOV: /* 自戰模式 */
		if (numDegrees < 0) { /* 回退 */
			onlymov.regainMove();
			printf("After update: %p\n", onlymov.curNode);
			curmov = onlymov.curNode->mov;
			update();
		}
		else if (numDegrees > 0) { /* 前進 與讀譜模式還是有區別的，因爲這是回滾來的 */
			if (onlymov.curNode->nxt.size() > 0) {
				onlymov.curNode = onlymov.curNode->nxt[0];
				player = onlymov.curNode->stoneProp;
				curmov = onlymov.curNode->mov;
				onlymov.configDropStone(player, curmov);
				update();
			}

		}
		break;
    case CAC_SIG: /* 讀譜模式 */
		if ((numDegrees > 0) && (current != NULL)) { /* 向前讀譜 */
			curmov = current->mov;
			if (onlymov.configDropStone(current->stoneProp, current->mov)) update();
			if (current->nxt.size() > 0) current = current->nxt[0];
		}
		else if (numDegrees < 0) { /* 回溯棋譜 */
			if (onlymov.regainMove()) return;
			current = onlymov.curNode;
			update();
		}
		break;
    default: break;
	}
}

void QtLancifolium::resizeEvent(QResizeEvent *resize) { /* 獲取更改後的棋盤大小 */
    int widt, heit, allsize;
    heit = resize->size().height();
    widt = resize->size().width();
    allsize = heit < widt ? heit : widt; /* 選擇小者 */
    printf("# resize [%d, %d]\n", widt, heit); /////////////////////

    win_size = allsize / 200 * 200;
    win_gap = win_size / 20;
    if (heit - win_size < 60) win_ylb = 29;
    else win_ylb = (heit - win_size) / 2;
    if (widt < win_size) win_xlb = 0;
    else win_xlb = (widt - win_size) / 2;

	setbuttgeometry(); /* refresh buttons' geometry */
    update(); /* 重畫棋盤 */
}


/* 按鈕關聯動作 */
void QtLancifolium::on_refresh() {
    if (cac == 0) cac = 1;
    else if (cac == 2) {
		current = sig.root;
	}
    onlymov.init();
    curmov = -1;
    update();
}

void QtLancifolium::on_openfile() {
    QString filename;
    sig.clearall();
    filename = QFileDialog::getOpenFileName(this, tr("Open Text"), ".", tr("Image Files(*.sgf)"));
    if (filename.isEmpty()) ;
    else {
		char *cfilename = filename.toLatin1().data();
		sig.configManual(cfilename);
		cac = CAC_SIG;
		current = sig.root;
		int tmpk = 0;
		while (true) { // 之前此處的終止條件錯誤
			current->printing();
			printf("|%d|", tmpk++);
			if (current->nxt.size() > 0) current = current->nxt[0];
			else break;
		}
		system("pause");
		current = sig.root;
		onlymov.init();
	}
}

void QtLancifolium::on_formatting() { // Two ways are okay
    static Formatting format;
    format.show();
}

void QtLancifolium::on_abstention() {
    static QtWithoutForm format;
    format.show();
}

/* 功能函數 */
void QtLancifolium::simplemoving(int movx, int movy) {
    int tmpx, tmpy;
    if ((movx >= win_xlb) && (movx < win_xlb + win_size) &&
		  (movy >= win_ylb) && (movy < win_ylb + win_size)) {
		tmpx = (movx - win_xlb - win_gap / 2) / win_gap;
		tmpy = (movy - win_ylb - win_gap / 2) / win_gap;
		switch (onlymov.configDropStone(player, tmpx * 100 + tmpy)) { // 著子
		case CAC_MOV:
		case CAC_SIG:
		case CAC_EDT:
			curmov = tmpx * 100 + tmpy;
			player = player == BLACKSTONE ? WHITESTONE : BLACKSTONE;
			update(); break;
		default: break;
		}
	}
}


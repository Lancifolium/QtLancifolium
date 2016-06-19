#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
	ui(new Ui::Widget)//, pain(this)
{
    ui->setupUi(this);
	cac = 1; // 默認爲打譜模式
	onlymov.init();
    imgbord.load(":/images/bord.png");
    imgb.load(":/images/stb.png");
    imgw.load(":/images/stw.png");
	player = 1;
	curmov = -1;
	current = NULL;

	// 按鈕字的顏色
	QPalette qpalref = ui->Refresh->palette();
	qpalref.setColor(QPalette::ButtonText, Qt::blue);
	ui->Refresh->setPalette(qpalref);
	ui->Next->setPalette(qpalref);
	ui->openfile->setPalette(qpalref);

	// 按鈕透明背景
	ui->Refresh->setFlat(true);
	ui->Next->setFlat(true);
	ui->openfile->setFlat(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::drawcube() {
	QPainter pain(this);
	brushs.setStyle(Qt::SolidPattern);
	brushs.setColor(Qt::blue);
	pain.setBrush(brushs);

	// 頂層四方
	pain.drawLine(200, 200, 44, 110);
	pain.drawLine(200, 200, 356, 110);
	pain.drawLine(44, 110, 200, 20);
	pain.drawLine(200, 20, 356, 110);

	//
	pain.drawLine(356, 110, 356, 290);
	pain.drawLine(356, 290, 200, 380);
	pain.drawLine(200, 380, 44, 290);
	pain.drawLine(44, 290, 44, 110);

	pain.drawLine(200, 200, 200, 380);
}
void Widget::drawbord() {
	QPainter pain(this);
	int tmpi;
	for (tmpi = 0; tmpi < 19; tmpi++) {
		pain.drawLine(15, 15 + tmpi * 30, 555, 15 + tmpi * 30);
		pain.drawLine(15 + tmpi * 30, 15, 15 + tmpi * 30, 555);
	}

	pain.drawEllipse(QPoint(105, 105), 2, 2);
	pain.drawEllipse(QPoint(105, 465), 2, 2);
	pain.drawEllipse(QPoint(465, 105), 2, 2);
	pain.drawEllipse(QPoint(465, 465), 2, 2);
	pain.drawEllipse(QPoint(285, 285), 2, 2);
	pain.drawEllipse(QPoint(105, 285), 2, 2);
	pain.drawEllipse(QPoint(465, 285), 2, 2);
	pain.drawEllipse(QPoint(285, 105), 2, 2);
	pain.drawEllipse(QPoint(285, 465), 2, 2);
}
void Widget::drawmoveApp() {
	QPainter pain(this);
	pain.setRenderHint(QPainter::Antialiasing, true); // 使得邊緣柔和
	int tmpi, tmpj;
	for (tmpi = 0; tmpi < 19; tmpi++) {
		for (tmpj = 0; tmpj < 19; tmpj++) {
			if (onlymov.ston[tmpi][tmpj] == 1) {
                //brushs.setColor(Qt::black);
                //pain.setBrush(brushs);
                //pain.drawEllipse(QPoint(tmpi * 30 + 15, tmpj * 30 + 15), 13, 13);
                pain.drawImage(tmpi * 30 + 16, tmpj * 30 + 16, imgb);
			}
			else if (onlymov.ston[tmpi][tmpj] == 2) {
                //brushs.setColor(Qt::white);
                //pain.setBrush(brushs);
                //pain.drawEllipse(QPoint(tmpi * 30 + 15, tmpj * 30 + 15), 13, 13);
                pain.drawImage(tmpi * 30 + 16, tmpj * 30 + 16, imgw);
			}
		}
	} // finished for
	if (curmov >= 0) {
		brushs.setColor(Qt::blue);
		pain.setBrush(brushs);
        pain.drawRect(curmov / 100 * 30 + 24, curmov % 100 * 30 + 24, 12, 12);
	}
}

void Widget::paintEvent(QPaintEvent *) {
	QPainter pain(this);
    //pain.drawImage(QPoint(0, 0), img); // 背景圖片
    pain.drawImage(QPoint(0, 0), imgbord); // 棋盤
	brushs.setStyle(Qt::SolidPattern); // 填充模式

    //drawbord(); // 繪製棋盤

	switch (cac) {
	case 1:
		drawmoveApp();

		break;
	case 2:
		drawmoveApp();
		break;
	default: break;
	}
} // end paintEvent

void Widget::moveSimpleApp(int lasx, int lasy) {
	int tmpx, tmpy;
    if ((lasx >= 15) && (lasx < 585) && (lasy >= 15) && (lasy < 585)) {
        tmpx = (lasx - 15) / 30;
        tmpy = (lasy - 15) / 30;
        switch (onlymov.configDropStone(player, tmpx * 100 + tmpy)) { // 著子
        case 0: break;
        case 1:
        case 2:
        case 3:
            curmov = tmpx * 100 + tmpy;
            player = player == 1 ? 2 : 1;
            update(); break;
        default: break;
		}
	}
}

void Widget::mouseReleaseEvent(QMouseEvent *las) {
    switch (cac) {
    case 0: break;
    case 1: // 自戰
		moveSimpleApp(las->x(), las->y());
		break;
	case 2: // 簡單讀譜
        if (onlymov.configDropStone(current->stoneProp, current->mov)) update();
		break;
    default: break;
    }
}

void Widget::wheelEvent(QWheelEvent *eve) {
	if (cac == 2) { // 前提是讀譜模式
		int numDegrees = eve->delta();
		if ((numDegrees > 0) && (current != NULL)) {
			curmov = current->mov;
            if (onlymov.configDropStone(current->stoneProp, current->mov)) update();
			current = current->next;
		}
	}
}

void Widget::on_Refresh_pressed()
{
	if (cac == 0) cac = 1;
	else if (cac == 2) {
		current = sgf.root;
		//system("pause");
		memset(sgf.ston, 0, sizeof(char) * 676);
		//system("pause");
	}
	onlymov.init();
	curmov = -1;
	//system("pause");
	update();
}

void Widget::on_openfile_pressed()
{
	QString filename;
	filename = QFileDialog::getOpenFileName(this, tr("Open Text"), ".", tr("Image Files(*.sgf)"));
	if (filename.isEmpty()) ;
	else {
		char *cfilename = filename.toLatin1().data();
		sgf.configManual(cfilename);
		cac = 2;
		current = sgf.root;
		int tmpk = 0;
		while (current != NULL) {
			current->printing();
			printf("|%d|", tmpk++);
			current = current->next;
		}
		current = sgf.root;
		onlymov.init();
	}
	//system("pause");
}

void Widget::on_Next_pressed()
{
	if (cac == 2) {
		if (current != NULL) {
			if (current->mov < 0) ;
			else if (current->stoneProp == 1 || current->stoneProp == 2) {
                onlymov.configDropStone(current->stoneProp, current->mov);
				curmov = current->mov;
				update();
			}
			current = current->next;
		} // if (current != NULL)
	} // end if (cac == 2)
}

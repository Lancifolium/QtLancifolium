#include "QtLancifolium.h"
#include "ui_QtLancifolium.h"

QtLancifolium::QtLancifolium(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtLancifolium)
{
    ui->setupUi(this);

    cac = 1; // 默認爲自戰模式
    onlymov.init();
    imgbord.load(":/images/bord.png");
    imgcur.load(":/images/move.png");
    imgb.load(":/images/movblack.png");
    imgw.load(":/images/movwhite.png");
    setWindowTitle("Lancifolium");

    win_gap = 30;
    win_size = 600;
    win_xlb = 10;
    win_ylb = 20;

    player = 1;
    curmov = -1;
    current = NULL;

    abstention = new QPushButton("&Abstention", this); // 棄權按鈕，注意parent是本框體
    abstention->setGeometry(win_xlb + win_size / 2 - 36, win_ylb + win_size,
                            72, 24);
}

QtLancifolium::~QtLancifolium()
{
    delete ui;
}

void QtLancifolium::drawmoveapp() {
    QPainter pain(this);
    pain.setRenderHint(QPainter::Antialiasing, true); // 使得邊緣柔和

    int tmpi, tmpj;
    //QRect source(0, 0, 66, 66);
    for (tmpi = 0; tmpi < 19; tmpi++) {
        for (tmpj = 0; tmpj < 19; tmpj++) {
            if (onlymov.ston[tmpi][tmpj] == 1) {
                QRect target(win_xlb + tmpi * win_gap + win_gap * 11 / 20,
                             win_ylb + tmpj * win_gap + win_gap * 11 / 20,
                             win_gap * 9 / 10,
                             win_gap * 9 / 10);
                //pain.drawImage(tmpi * win_gap + win_xlb, tmpj * win_gap + win_ylb, imgb);
                pain.drawImage(target, imgb);
            }
            else if (onlymov.ston[tmpi][tmpj] == 2) {
                QRect target(win_xlb + tmpi * win_gap + win_gap * 11 / 20,
                             win_ylb + tmpj * win_gap + win_gap * 11 / 20,
                             win_gap * 9 / 10,
                             win_gap * 9 / 10);
                //pain.drawImage(tmpi * win_gap + win_xlb, tmpj * win_gap + win_ylb, imgb);
                pain.drawImage(target, imgw);
            }
        }
    } // finished for

    if (curmov >= 0) {
        brushs.setColor(Qt::cyan);
        pain.setBrush(brushs);
        QPolygon pts;
        pts.setPoints(3,
                      win_xlb + curmov / 100 * win_gap + win_gap,
                      win_ylb + curmov % 100 * win_gap + win_gap,
                      win_xlb + curmov / 100 * win_gap + win_gap,
                      win_ylb + curmov % 100 * win_gap + win_gap * 29 / 20,
                      win_xlb + curmov / 100 * win_gap + win_gap * 29 / 20,
                      win_ylb + curmov % 100 * win_gap + win_gap);
        pain.drawPolygon(pts); // 畫三角形
    }
}

void QtLancifolium::paintEvent(QPaintEvent *) {
    QPainter pain(this);
    QRect target(win_xlb, win_ylb, win_size, win_size);
    pain.drawImage(target, imgbord); // 棋盤
    brushs.setStyle(Qt::SolidPattern); // 填充模式

    //drawbord(); // 繪製棋盤

    switch (cac) {
    case 1:
        drawmoveapp();
        break;
    case 2:
        drawmoveapp();
        break;
    default: break;
    }
} // paintEvent

void QtLancifolium::mouseReleaseEvent(QMouseEvent *las) {
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

void QtLancifolium::wheelEvent(QWheelEvent *eve) {
    int numDegrees = eve->delta();
    if (cac == 2) { // 前提是讀譜模式
        if ((numDegrees > 0) && (current != NULL)) {
            curmov = current->mov;
            if (onlymov.configDropStone(current->stoneProp, current->mov)) update();
            if (current->nxt.size() > 0) current = current->nxt[0];
        }
        else if (numDegrees < 0) {

            if (current == NULL) {

                return;
            }
            onlymov.regainMove();
            current = onlymov.curNode;
            update();
        }
    }
    else if (cac == 1) { // 自戰模式
        if (numDegrees < 0) {
            onlymov.regainMove(); //
            printf("After update: %d\n", onlymov.curNode);
            update();
        }
    }
}

void QtLancifolium::resizeEvent(QResizeEvent *resize) { // 獲取更改後的棋盤大小
    int widt, heit, allsize;
    heit = resize->size().height();
    widt = resize->size().width();
    allsize = heit < widt ? heit : widt; // 選擇小者
    printf("# resize [%d, %d]\n", widt, heit);
    switch (allsize / 200) {
    case 0:
    case 1:
    case 2: // 400x400
        win_size = 400;
        break;
    case 3: // 600x600
        win_size = 600;
        break;
    case 4: // 800x800
        win_size = 800;
        break;
    case 5: // 1000x1000
        win_size = 1000;
        break;
    case 6: // 1200x1200
        win_size = 1200;
        break;
    case 7: // 1400x1400
        win_size = 1400;
        break;
    case 8: // 1600x1600
        win_size = 1600;
        break;
    default:
        win_size = 600;
        break;
    }
    win_gap = win_size / 20;
    if (heit - win_size < 40) { // 此處考慮工具欄
        win_ylb = 20;
    }
    else win_ylb = (heit - win_size) / 2;
    if (widt < win_size) win_xlb = 0;
    else win_xlb = (widt - win_size) / 2;
    abstention->setGeometry(win_xlb + win_size / 2 - 36, win_ylb + win_size,
                            72, 24);
    update(); // 重畫棋盤
}

void QtLancifolium::moveSimpleApp(int movx, int movy) {
    int tmpx, tmpy;
    if ((movx >= win_xlb) &&
        (movx < win_xlb + win_size) &&
        (movy >= win_ylb) &&
        (movy < win_ylb + win_size)
    ) {
        tmpx = (movx - win_xlb - win_gap / 2) / win_gap;
        tmpy = (movy - win_ylb - win_gap / 2) / win_gap;
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

void QtLancifolium::on_actionRefresh_triggered()
{
    if (cac == 0) cac = 1;
    else if (cac == 2) {
        current = sgf.root;
    }
    onlymov.init();
    curmov = -1;
    update();
}

void QtLancifolium::on_actionOpen_File_triggered()
{
    QString filename;
    sgf.clearall();
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
            if (current->nxt.size() > 0) current = current->nxt[0];
        }
        current = sgf.root;
        onlymov.init();
    }
    //system("pause");
}

void QtLancifolium::on_actionFormat_File_triggered()
{ // Two ways are okay
    static Formatting format;
    format.show();
}

void QtLancifolium::on_actionTestOnly_triggered()
{
    static QtWithoutForm format;
    format.show();
}

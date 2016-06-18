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
    imgb.load(":/images/stb.png");
    imgw.load(":/images/stw.png");
    setWindowTitle("Lancifolium");
    player = 1;
    curmov = -1;
    current = NULL;

    // 按鈕字的顏色
    QPalette qpalref = ui->Refresh->palette();
    qpalref.setColor(QPalette::ButtonText, Qt::blue);
    ui->Refresh->setPalette(qpalref);
    ui->openfile->setPalette(qpalref);

    // 按鈕透明背景
    ui->Refresh->setFlat(true);
    ui->openfile->setFlat(true);
}

QtLancifolium::~QtLancifolium()
{
    delete ui;
}

void QtLancifolium::drawmoveapp() {
    QPainter pain(this);
    pain.setRenderHint(QPainter::Antialiasing, true); // 使得邊緣柔和
    int tmpi, tmpj;
    for (tmpi = 0; tmpi < 19; tmpi++) {
        for (tmpj = 0; tmpj < 19; tmpj++) {
            if (onlymov.ston[tmpi][tmpj] == 1) {
                pain.drawImage(tmpi * 30 + 16, tmpj * 30 + 16, imgb);
            }
            else if (onlymov.ston[tmpi][tmpj] == 2) {
                pain.drawImage(tmpi * 30 + 16, tmpj * 30 + 16, imgw);
            }
        }
    } // finished for
    if (curmov >= 0) {
        brushs.setColor(Qt::blue);
        pain.setBrush(brushs);
        pain.drawImage(curmov / 100 * 30 + 30, curmov % 100 * 30 + 30, imgcur);
        //pain.drawRect(curmov / 100 * 30 + 24, curmov % 100 * 30 + 24, 12, 12);
    }
}

void QtLancifolium::paintEvent(QPaintEvent *) {
    QPainter pain(this);
    pain.drawImage(QPoint(0, 0), imgbord); // 棋盤
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
            if (current->next != NULL) current = current->next;
        }
        else if (numDegrees < 0) {
            if (onlymov.moveList.empty()) {
                current = sgf.root;
                while (!onlymov.bordList.empty()) onlymov.bordList.pop_back();
                return;
            }
            int tmpcurr = onlymov.moveList.back(); // 先取出棧頂沒錯，這是當前move

            if (tmpcurr > 10000) {
                onlymov.regainMove(); // 恢復棋盤
                tmpcurr %= 10000;
            }

            onlymov.ston[tmpcurr / 100][tmpcurr % 100] = 0; // 撤銷著子

            onlymov.moveList.pop_back(); // 彈出棧頂

            if (onlymov.moveList.empty()) {
                curmov = -1;
                player = 1;
            }
            else {
                curmov = onlymov.moveList.back();
                player = player == 1 ? 2 : 1;
            }

            if (current != NULL && current->parent != NULL) current = current->parent; //

            update();
        }
    }
    else if (cac == 1) { // 自戰模式
        if (numDegrees < 0) {
            if (onlymov.moveList.empty()) {
                printf("Empty!!!!!!\n");
                return;
            }
            int tmpcurr = onlymov.moveList.back(); // 先取出棧頂沒錯，這是當前move

            if (tmpcurr > 10000) {
                onlymov.regainMove(); // 恢復棋盤
                tmpcurr %= 10000;
            }

            onlymov.ston[tmpcurr / 100][tmpcurr % 100] = 0; // 撤銷著子

            onlymov.moveList.pop_back(); // 彈出棧頂

            if (onlymov.moveList.empty()) {
                curmov = -1;
                player = 1;
            }
            else {
                curmov = onlymov.moveList.back();
                player = player == 1 ? 2 : 1;
            }

            update();
        }
    }
}

void QtLancifolium::moveSimpleApp(int movx, int movy) {
    int tmpx, tmpy;
    if ((movx >= 15) && (movx < 585) && (movy >= 15) && (movy < 585)) {
        tmpx = (movx - 15) / 30;
        tmpy = (movy - 15) / 30;
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

void QtLancifolium::on_openfile_released()
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

void QtLancifolium::on_Refresh_released()
{
    if (cac == 0) cac = 1;
    else if (cac == 2) {
        current = sgf.root;
        //system("pause");
        //memset(sgf.ston, 0, sizeof(char) * 676);
        //system("pause");
    }
    onlymov.init();
    curmov = -1;
    //system("pause");
    update();
}

void QtLancifolium::on_formatfile_released()
{
    //Formatting *format;
    //format = new Formatting;
    //format->show();
    static Formatting format;
    format.show();
}

#include "Formatting.h"

Formatting::Formatting(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Lancifolium Formatting");

    QPalette qpalref;// = ui->formopenfile->palette();
    qpalref.setColor(QPalette::ButtonText, Qt::blue);
    formopenfile->setPalette(qpalref);
    formsavefile->setPalette(qpalref);

    formopenfile->setFlat(true); // 按鈕透明背景
    formsavefile->setFlat(true);

    QIcon fopenfil(":/images/folder_blue_open.png");
    formopenfile->setIcon(fopenfil);
    QIcon fsavefil(":/images/filesave.png");
    formsavefile->setIcon(fsavefil);
}

Formatting::~Formatting() {
    delete ui;
}

void Formatting::on_formopenfile_released() {
    infilename = QFileDialog::getOpenFileName(this, tr("Open Text"), ".", tr("SGF Files(*.sgf)"));
}

void Formatting::on_formsavefile_released() {
    oufilename = QFileDialog::getSaveFileName(this, tr("Open Text"), ".", tr("SGF Files(*.sgf)"));
    if (oufilename.isEmpty()) ;
    else if (infilename.isEmpty()) ;
    else {
        char *infile = infilename.toLatin1().data();
        char *oufile = oufilename.toLatin1().data();
        if (Funs::ManualAdjustment(infile, oufile)) {
            QMessageBox::information(this, "Formatting result", "Formatting successful! ");
        }
        else QMessageBox::information(this, "Formatting result", "Failed! ");
    }
}

void Formatting::resizeEvent(QResizeEvent *resize) {

}

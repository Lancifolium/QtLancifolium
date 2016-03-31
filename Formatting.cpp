#include "Formatting.h"
#include "ui_Formatting.h"

Formatting::Formatting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Formatting)
{
    ui->setupUi(this);
    setWindowTitle("Lancifolium Formatting");
}

Formatting::~Formatting()
{
    delete ui;
}

void Formatting::on_formopenfile_released()
{
    infilename = QFileDialog::getOpenFileName(this, tr("Open Text"), ".", tr("SGF Files(*.sgf)"));
}

void Formatting::on_formsavefile_released()
{
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

#ifndef FORMATTING_H
#define FORMATTING_H

#include <QDialog>
#include <QFileDialog>
#include <QApplication>
#include <QString>
#include <QMessageBox>
#include <QPalette>
#include "FunLancifolium.h"

namespace Ui {
class Formatting;
}

class Formatting : public QDialog
{
    Q_OBJECT

public:
    explicit Formatting(QWidget *parent = 0);
    ~Formatting();

private slots:
    void on_formopenfile_released();

    void on_formsavefile_released();

private:
    Ui::Formatting *ui;

    QString infilename; // insert filename
    QString oufilename; // output filename
};

#endif // FORMATTING_H

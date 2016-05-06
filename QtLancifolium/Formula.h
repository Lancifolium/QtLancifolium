#ifndef FORMULA_H
#define FORMULA_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QFileDialog>
#include <QApplication>
#include <QString>
#include <QMessageBox>
#include <QPalette>
#include <QPushButton>
#include <QResizeEvent>
#include "Lancifolium/DevLancifolium.h"

/* 先試著實現一個簡單的打譜界面再說 */
struct Formula : public QWidget {
	Q_OBJECT
public:
	Formula(QWidget *parent = 0);

private:

};

#endif // FORMULA_H

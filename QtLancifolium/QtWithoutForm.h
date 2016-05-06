#ifndef QTWITHOUTFORM_H
#define QTWITHOUTFORM_H

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
#include "testing.h"

struct QtWithoutForm : public QWidget {
public:
    QtWithoutForm(QWidget *parent = 0);
    QPushButton *button;

    void resizeEvent(QResizeEvent *);

};

#endif // QTWITHOUTFORM_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include "widget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    FFTWidget *fftwidget;
    QComboBox *window_chooser;

public:
    explicit MainWindow(QWidget *parent = 0);
    
signals:
    
public slots:
    void changeWindow(int idx);
};

#endif // MAINWINDOW_H

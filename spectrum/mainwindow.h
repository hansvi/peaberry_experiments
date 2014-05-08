#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QSlider>
#include "widget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    FFTWidget *fftwidget;
    QComboBox *window_chooser;
    QSlider *frequency_offset;


public:
    explicit MainWindow(QWidget *parent = 0);
    
signals:
    
public slots:
    void setWindow(int idx);
    void setFrequencyOffset(int val);
};

#endif // MAINWINDOW_H

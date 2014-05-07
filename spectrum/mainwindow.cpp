#include "mainwindow.h"
#include <QBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    fftwidget = new FFTWidget;
    window_chooser = new QComboBox;
    window_chooser->addItem("Rectangular");
    window_chooser->addItem("Hann");
    window_chooser->addItem("Blackman-Harris");
    QVBoxLayout *top = new QVBoxLayout;
    QHBoxLayout *buttons = new QHBoxLayout;
    buttons->addWidget(window_chooser);
    buttons->addStretch();
    top->addWidget(fftwidget);
    top->addLayout(buttons);

    QWidget *central = new QWidget;
    central->setLayout(top);
    setCentralWidget(central);
    connect(window_chooser, SIGNAL(currentIndexChanged(int)), this, SLOT(changeWindow(int)));
}


void MainWindow::changeWindow(int idx)
{
    if(idx==1)
        fftwidget->setHannWindow();
    else if(idx==2)
        fftwidget->setBlackmanHarrissWindow();
    else
        fftwidget->setRectWindow();
}

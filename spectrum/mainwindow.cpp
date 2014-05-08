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
    frequency_offset = new QSlider(Qt::Horizontal);
    frequency_offset->setRange(-512,512);
    frequency_offset->setValue(0);

    QVBoxLayout *top = new QVBoxLayout;
    QHBoxLayout *buttons = new QHBoxLayout;
    buttons->addWidget(window_chooser);
    buttons->addWidget(frequency_offset);
    buttons->addStretch();
    top->addWidget(fftwidget);
    top->addLayout(buttons);

    QWidget *central = new QWidget;
    central->setLayout(top);
    setCentralWidget(central);
    connect(window_chooser, SIGNAL(currentIndexChanged(int)), this, SLOT(setWindow(int)));
    connect(frequency_offset, SIGNAL(valueChanged(int)), this, SLOT(setFrequencyOffset(int)));
}


void MainWindow::setWindow(int idx)
{
    if(idx==1)
        fftwidget->setHannWindow();
    else if(idx==2)
        fftwidget->setBlackmanHarrissWindow();
    else
        fftwidget->setRectWindow();
}

void MainWindow::setFrequencyOffset(int val)
{
    fftwidget->setOffsetFrequency(float(val));
}

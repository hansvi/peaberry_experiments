#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <complex>
#include <alsa/asoundlib.h>
#include <qtimer.h>

class FFTWidget : public QWidget
{
    Q_OBJECT
    std::complex<float> buffer[1024];
    float window_function[1024];
    snd_pcm_t *capture_handle;
    QTimer *timer;

public:
    FFTWidget(QWidget *parent = 0);
    ~FFTWidget();
public slots:
    void processFFT();
    void setHannWindow();
    void setRectWindow();
    void setBlackmanHarrissWindow();
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // WIDGET_H

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
    std::complex<float> window_function[1024];
    float offset_freq;
    snd_pcm_t *capture_handle;
    QTimer *timer;
    enum
    {
        RectangularWindow,
        HannWindow,
        BlackmanHarrissWindow
    } current_window;

    void updateWindowFunction();
    std::complex<float> f_offset(int i, float maxval);

public:
    FFTWidget(QWidget *parent = 0);
    ~FFTWidget();
public slots:
    void processFFT();
    void setHannWindow();
    void setRectWindow();
    void setBlackmanHarrissWindow();
    void setOffsetFrequency(float f);
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // WIDGET_H

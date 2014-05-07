#include "widget.h"
#include <qpainter.h>
#include <qpainterpath.h>
#include <../fftbench/fft.hpp>

FFTWidget::FFTWidget(QWidget *parent)
    : QWidget(parent)
{
    int err;
    snd_pcm_hw_params_t *hw_params;
    const char *dev_name = "hw:SDR";
    if ((err = snd_pcm_open(&capture_handle, dev_name, SND_PCM_STREAM_CAPTURE, 0)) < 0)
    {
        fprintf (stderr, "cannot open audio device %s (%s)\n",
                 dev_name,
                 snd_strerror (err));
        exit (1);
    }

    if ((err = snd_pcm_hw_params_malloc(&hw_params)) < 0)
    {
        fprintf (stderr, "cannot allocate hardware parameter structure (%s)\n",
                 snd_strerror (err));
        exit (1);
    }

    if ((err = snd_pcm_hw_params_any(capture_handle, hw_params)) < 0)
    {
        fprintf (stderr, "cannot initialize hardware parameter structure (%s)\n",
                 snd_strerror (err));
        exit (1);
    }

    if ((err = snd_pcm_hw_params_set_access(capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
    {
        fprintf (stderr, "cannot set access type (%s)\n",
                 snd_strerror (err));
        exit (1);
    }

    if ((err = snd_pcm_hw_params_set_format(capture_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0)
    {
        fprintf (stderr, "cannot set sample format (%s)\n",
                 snd_strerror (err));
        exit (1);
    }

    if ((err = snd_pcm_hw_params_set_rate(capture_handle, hw_params, 96000, 0)) < 0)
    {
        fprintf (stderr, "cannot set sample rate (%s)\n",
                 snd_strerror (err));
        exit (1);
    }

    if ((err = snd_pcm_hw_params_set_channels (capture_handle, hw_params, 2)) < 0)
    {
        fprintf (stderr, "cannot set channel count (%s)\n",
                 snd_strerror (err));
        exit (1);
    }

    if ((err = snd_pcm_hw_params (capture_handle, hw_params)) < 0)
    {
        fprintf (stderr, "cannot set parameters (%s)\n",
                 snd_strerror (err));
        exit (1);
    }

    snd_pcm_hw_params_free (hw_params);

    if ((err = snd_pcm_prepare (capture_handle)) < 0)
    {
        fprintf (stderr, "cannot prepare audio interface for use (%s)\n",
                 snd_strerror (err));
        exit (1);
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(processFFT()));
    timer->start(); // Zero-delay
    if((err = snd_pcm_start(capture_handle)) < 0)
    {
        fprintf (stderr, "cannot start audio interface (%s)\n",
                 snd_strerror (err));
        exit(1);
    }
}

FFTWidget::~FFTWidget()
{
    snd_pcm_close(capture_handle);
}

void FFTWidget::processFFT()
{
    int avail = snd_pcm_avail(capture_handle);
    if(avail<0)
    {
        fprintf (stderr, "Cannot read audio samples (%s)\n",
                 snd_strerror (avail));
        exit(1);
    }
    if(avail > (2*1024))
    {
        short input[2*1024];
        int err;
        if ((err = snd_pcm_readi(capture_handle, input, 1024)) != 1024)
        {
            fprintf(stderr, "read from audio interface failed (%s)\n",
                    snd_strerror (err));
            exit(1);
        }
        for(int i=0; i<1024; i++)
        {
            buffer[i]= std::complex<float>(input[2*i+1]/32768.0, input[2*i]/32768.0);
        }
        FFT::dft(buffer);
        update();
    }
}

void FFTWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    QPainterPath path(QPointF(0, 99.0-100*std::abs(buffer[0])));
    // Make the viewport size 512x100
    painter.scale(width()/1024.0, height()/100.0);
    for(int i=1; i<1024;i++)
    {
        path.lineTo(QPointF(i, 100.0-1000*std::abs(buffer[i])));
    }
    painter.drawPath(path);
}

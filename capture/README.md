capture
=======

Very simple example based on http://equalarea.com/paul/alsa-audio.html

* Opens the Peaberry ALSA device for capture
* Reads I/Q samples, converts them to normalized floats (range between -1.0 and 1.0) and writes them to stdout.

The output can be piped to a file, and used later with gnuradio, gqrx etc.



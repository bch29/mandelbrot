mandelbrot
==========

A Mandelbrot Set visualiser written in C++ with the SDL2 library.

* To scroll around, right-click and drag.
* To zoom in, left-click and drag downwards.
* To zoom out, left-click and drag upwards.

Each time you zoom or scroll, the set is recalculated, which may take a long time -- longer if you are further zoomed in. Attempting to zoom or scroll while the set is being recalculated will trigger another recalculation without doing anything. I plan on fixing that when I have time.

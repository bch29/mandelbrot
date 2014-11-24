mandelbrot
==========

A Mandelbrot Set visualiser written in C++ with the SDL2 library.

* To scroll around, right-click and drag.
* To zoom in, left-click and drag downwards.
* To zoom out, left-click and drag upwards.

Each time you zoom or scroll, the set is recalculated, which may take a long time -- longer if you are further zoomed in. Attempting to zoom or scroll while the set is being recalculated will trigger another recalculation without doing anything. I plan on fixing that when I have time.

===
### Compiling
* You may have to edit the makefile to specify the directories of the SDL2 headers and libraries.
* Run `make build` from the command line to build, or `make run` to run the program.
* Tested under Ubuntu 14.04 LT, but should work on any operating system supported by SDL2.

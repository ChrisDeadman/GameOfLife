
GameOfLife v1.0
===============

Author: ChrisDeadman

Simple implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) in C++11.

## Dependencies
* cmake (`apt-get install cmake`)
* libpthreads (`apt-get install libpthread-stubs0-dev`)
* libsdl2 (`apt install libsdl2-dev libsdl2-ttf-dev`)
* libgtest (downloaded and compiled automatically)

## Compiling
* `cd GameOfLife`
* `mkdir build`
* `cd build`
* `cmake ../` (or `cmake ../ -Dtest=ON` to include tests) 
* `make`

## Running
* `cd GameOfLife`
* `cd build`
* run application: `src/main/gameOfLife`
* run tests: `src/test/gameOfLife_test`

## Tested Operating Systems
* Linux (tested on Ubuntu 17.10)

## 3rd party credits
* [Google Open Sans font](https://fonts.google.com/specimen/Open+Sans)

Release notes
=======================

### GameOfLife v1.0
* Initial release

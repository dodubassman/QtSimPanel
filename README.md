# QtSimPanel

External instrument panels for X-Plane (and MSF2020 soon!)

QtSimPanel will provide functional aircraft gauges and instruments to be display on a light computer or RasberryPi. It is aimed to be connected to the same network the main X-plane computer is running.

Todo list :

- [ ] Add the possibility to choose UDPClient interface : X-Plane / MFS2020
- [ ] Add the possibility to choose among a collection of flight panels (only Basic 6 / Robin DR400 is hard coded right now)
- [ ] Provide compiled files for Rapberry, Mac and windows (linux 64 only at the moment0

QtSimPanel is writen in C++ / QML using Qt5.


## Build

With Cmake:

```
$ mkdir build
$ cd build/
$ cmake ../
$ make
```

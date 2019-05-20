# JAGCS
Joint architecture ground control station. Or just another ground control station:)

[![Build Status](https://travis-ci.org/MishkaRogachev/JAGCS.svg?branch=master)](https://travis-ci.org/MishkaRogachev/JAGCS)

![alt tag](https://raw.githubusercontent.com/MishkaRogachev/JAGCS/master/ui.png)

Can be used as ground software for the drones, but other information protocols can be integrated.
Build with Qt and works on Windows/Linux/Android(Mac support will be later).

### Source code
Clone using git with command
```
git clone --recursive https://github.com/MishkaRogachev/JAGCS.git
```

### Dependencies
 
  * C++14 compiler
  * Qt 5.9 or higher
  * CMake 3.0 or higher

  GCC version 4.9 or higher required for MapBox GL QtLocation plugin
  ANGLE API is required for MapBox GL under windows

### Building desktop(Windows/Linux/Mac) application
```
mkdir build
cd build
cmake ..
make
```

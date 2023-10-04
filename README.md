# Autonomous vehicle #

Educational project from automotive domain.
Its goal is to create mobile robots with sensor and utilizing some knowledge from ADAS systems.
Project consist of 3 entities:

 - Robot application: application executed in Raspberry PI module. It consist as a driver.
 - ClientApp: Gui application to controll a robot. 
 - PythonAccessLib: Library to controll robot from python scripts.
 
## Vehicle ##

Vehicle consist of:

 - Raspberry PI 4 version B

## Environment setup
### Build environment for PC ###

Install boost libraries:

 - mkdir boost 
 - cd boost
 - wget https://boostorg.jfrog.io/artifactory/main/release/1.79.0/source/boost_1_79_0.tar.gz
 - tar -xzvf boost_1_79_0.tar.gz
 - cd boost_1_79_0/
 - ./bootstrap.sh
 - sudo ./b2 install --prefix=/usr/local

Install CV libraries
Install GoogleTest and google Mock
Install QT

And then build as any CMake projects:

 - mkdir build && cd build
 - cmake ..
 - make all

### Build environment for RaspberryPi ###

Robot driver is to be build on the module (Raspberry Pi) itself. It need to be installed:

 - boost libraries:
 - OpenCV library

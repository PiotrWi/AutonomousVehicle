# Autonomous vehicle #

Educational project from automotive domain.
Its goal is to create mobile robots with sensor and utilizing some knowledge from ADAS systems.
Project can be run in 2 environments:

 - Local PC. Here we can execute some "hardware in the loop" tests before we deploy software to real target.
 - Raspberry PI based machine. 

## Vehicle ##
Vehicle consist of:

 - Raspberry PI 4 version B

## Environment setup
Build environment for PC
Install boost libraries:

 - mkdir boost 
 - cd boost
 - wget https://boostorg.jfrog.io/artifactory/main/release/1.79.0/source/boost_1_79_0.tar.gz
 - tar -xzvf boost_1_79_0.tar.gz
 - cd boost_1_79_0/
 - ./bootstrap.sh
 - sudo ./b2 install --prefix=/usr/local

Install CV libraries

 - mkdir opencv
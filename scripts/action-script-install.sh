#!/bin/bash

echo "I will first install dependencies using conan"
mkdir build && cd build && conan install .. --build=missing
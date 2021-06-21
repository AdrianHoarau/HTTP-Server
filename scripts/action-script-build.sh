#!/bin/bash

echo "Building the project"
cd build && cmake .. -G "Unix Makefiles" && cmake --build .
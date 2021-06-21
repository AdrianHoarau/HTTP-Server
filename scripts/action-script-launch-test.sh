#!/bin/bash

echo "I will now launch the unit test command"
cd build && cd tests/bin/ && ./unit_tests_server
./unit_tests_snake
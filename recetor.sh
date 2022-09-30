#!/bin/bash
gcc -Wall -o read read_noncanonical.c stateMachine.c && ./read /dev/ttyS11
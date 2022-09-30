#!/bin/bash
gcc -Wall -o write write_noncanonical.c stateMachine.c  && ./write /dev/ttyS10
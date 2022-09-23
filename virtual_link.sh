#!/bin/bash
# This script is used to create a virtual link between two interfaces
sudo socat -d  -d  PTY,link=/dev/ttyS10,mode=777   PTY,link=/dev/ttyS11,mode=777
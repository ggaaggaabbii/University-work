#!/bin/bash

#Find the full names of all the users whose username ends in 88

cat passwd.fake | grep "^[a-zA-Z]\{4\}[0-9]\{2\}88" | awk -F ':' '{print $5}'

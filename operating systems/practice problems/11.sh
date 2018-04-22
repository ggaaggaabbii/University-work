#!/bin/bash

#Calculate the average of the PIDs of the processes currently running in the system.

cat ps.fake | awk -f 11.awk

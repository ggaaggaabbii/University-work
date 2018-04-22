#!/bin/bash

#Display all the distinct TTYs used by user root.

cat ps.fake | grep "root" | awk '{print $6}' | sort | uniq

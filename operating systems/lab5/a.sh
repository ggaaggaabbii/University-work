#!/bin/bash

cat last.fake | awk '{print $1 " "$10}' | sort | sed s/"[()]"//g | grep "popb" | awk '{print $1":"$2}' | awk -f a.awk


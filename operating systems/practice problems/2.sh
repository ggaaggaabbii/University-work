#!/bin/bash

#Find all the users that logged into the system after 11PM

cat last.fake | grep "23:[0-9]\{2\}" | sed s/"^\([^ ]\+\).\+23:[0-9]\{2\} - .\+"/"\1"/g | grep "^[0-9a-zA-Z]\+$" | sort | uniq

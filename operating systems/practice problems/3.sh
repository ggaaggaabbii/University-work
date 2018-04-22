#!/bin/bash

#Display the full names of the users having a username that starts with "m" and with a user ID divisible by 7.

cat passwd.fake | grep "^m[a-zA-Z]\{3\}\([0-9]\{4\}\)" | awk -F ':' '{if ( $3 % 7 == 0 ) print $5}'

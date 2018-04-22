#!/bin/bash

#Display all the mounted file systems who have either less then 1GB or less than 10%
#free space. space.

df --block-size=1073741824 | awk 'BEGIN{n=0}{if(n!=0){print $0}else{n=1}}' | \
    awk '{split($5, a, "%");if(a[1] > 90 || $4 < 1){print $1}}'

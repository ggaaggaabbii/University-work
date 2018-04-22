#!/bin/bash

#A - print the longest alphabetical lower case argument from a given list

m=0
rez=""

for i in $*; do
    r=`echo $i | sed "s/[^a-z]//g"`
    if [ ! -z $r ];then
        if [ $i = $r ]; then
            if [ `echo $rez | wc -m` -lt `echo $i | wc -m` ]; then
                m=`echo $i | wc -m`
                rez=$i
            fi
        fi
    fi
done

if [ $m -eq 0 ]; then
    echo No alphabetic lower case argument
    exit
fi

echo $rez

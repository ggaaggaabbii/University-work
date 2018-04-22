#!/bin/bash

#calculate the difference between the number of woels and consonants of
#the given arguments

if [ $# = 0 ]; then
    echo No argument

fi

v=0
c=0

while [ ! -z $1 ]; do
    i=`echo $1 | sed "s/[^a-zA-Z]//g"`
    v=$[$v + `echo $i | sed "s/[^aeiouAEIOU]//g" | wc -m` - 1]
    c=$[$c + `echo $i | sed "s/[aeiouAEIOU]//g" | wc -m` - 1]
    shift
done

echo "v: $v c: $c"

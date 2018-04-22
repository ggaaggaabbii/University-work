#!/bin/bash

#read a prefix and a number of words and check how many words contain the given prefix

sum=0
pref=$1
shift
for i in $*;do
	s=`echo $i | grep "^$pref"`
	if [ ! -z $s ];then
		sum=`expr $sum + 1`
	fi
done
echo $sum

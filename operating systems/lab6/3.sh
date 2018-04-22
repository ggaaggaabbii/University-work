#!/bin/bash

#se primesc oricate nume de fisiere sa se afiseze numarul mediu de cuvinte din fisier

sum=0
nr=0
for i in $*;do
	if [ -f $i ];then
		w=`cat $i | wc -w`
		sum=`expr $sum + $w`
		nr=`expr $nr + 1`
	fi
done
if [ $nr -ne 0 ];then
	echo `expr $sum / $nr`
else
	echo "No valid file"
fi

#!/bin/bash

#read file names and count the lines until you reach 10 lines and print the number of lines

sum=0;

while [ $sum -lt 10 ];do
	read u
	if [ -f $u ];then
		s=`wc -l $u | cut -f1 -d ' '`
		sum=`expr $sum + $s`
	fi	
done
echo $sum

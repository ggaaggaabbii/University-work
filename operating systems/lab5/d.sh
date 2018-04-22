#!/bin/bash

#primeste un prefix urmat de oricate cuvinte sa se afiseze cate dintre cuvinte sunt prefixate de cuv dat

p=$1
shift

while [ $1 ];do
	grep $p $1 | echo $1
done

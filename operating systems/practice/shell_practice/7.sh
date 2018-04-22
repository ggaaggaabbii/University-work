#!/bin/bash



function e {

    if [ $1 != "." -a $1 != "7.sh" ]; then
        echo $1
    fi

    if [ -d $1 ]; then
        for i in $(ls $1); do
            e $i
        done
    fi

}

e .

#for i in $(ls); do
#    e $i
#done

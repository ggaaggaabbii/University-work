#!/bin/bash

options="Hello Exit"
select opt in $options; do
    if [ "$opt" = "Exit" ]; then
        echo "Exiting..."
        exit
    elif [ "$opt" = "Hello" ]; then
        echo "Hello World !"
    else
        echo Bad option
    fi
done

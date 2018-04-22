#!/bin/bash

function hello {
    local HELLO=Hello
    echo $HELLO
}
#hello
echo ls
exit
echo $(ls)

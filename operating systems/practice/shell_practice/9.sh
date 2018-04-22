#!/bin/bash

#Consider a file containing a username on each line. Check whether the users exist,
#and generate an comma-separated string of emails. The email is obtained by appending
#"@scs.ubbcluj.ro" at the end of each username. Make sure the generated string does
#NOT end in a comma.

if [ $# -lt 1 ]; then
    echo No file given
    exit
fi

if [ ! -f $1 ]; then
    echo Not a valid file
    exit
fi

final=""

while read user; do
    if [ -z $user ]; then
        continue
    fi
    a=$(finger $user 2>error)
    if [ -z "$(cat "error" | grep "no such user")" ]; then
        final=$final$user@scs.ubbcluj.ro,
    fi
done < $1

if [ -f "error" ]; then
    rm "error"
fi

tmp=$(expr substr $final 1 $(expr length $final - 1))
echo $tmp


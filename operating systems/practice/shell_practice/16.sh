#!/bin/bash

#Delete recursively from a given directory all the files ending in "~", without
#asking for confirmation.

find | awk '/~$/{print $0}' | xargs rm -rf

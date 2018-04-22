#!/bin/bash

#Find all the usernames that logged in from "economica" on a Sunday

cat last.fake | grep "[^ ]\+.\+economica.ubbclu.\+Sun" | sed s/"^\([^ ]\+\).\+"/"\1"/g | sort | uniq

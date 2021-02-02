#!/bin/bash

for dir in /proc/*/fd;
do
    echo -n "$dir ";
    pid=`expr "$dir" : '\/proc\/\(.*\)\/.*'`; # extract the pid
    pname=`ps -p $pid -o comm=`; # grab process name
    echo -n "$pname ";
    ls $dir 2>/dev/null | wc -l;
done | sort -n -k 3

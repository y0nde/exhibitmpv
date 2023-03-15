#!/bin/sh

nrow=`ps | grep 'mpv -' | wc -l`
if [ $nrow -ge 2 ]; then
    echo 'alread active'
else 
    mpv - --input-ipc-server=/tmp/socket --keep-open --keep-open-pause=no
fi

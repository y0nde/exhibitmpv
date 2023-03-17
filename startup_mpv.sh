#!/bin/sh

nrow=`pgrep 'mpv -' | wc -l`
if [ $nrow -ge 1 ]; then
    echo 'alread active'
else 
    mpv - -fs --input-ipc-server=/tmp/mpvsocket --keep-open --keep-open-pause=no -vo=gpu

fi

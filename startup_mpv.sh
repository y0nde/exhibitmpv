#!/bin/sh

nrow=`pgrep 'mpv' | wc -l`
if [ $nrow -ge 1 ]; then
    echo 'alread active'
else 
    mpv - --input-ipc-server=/tmp/socket --keep-open --keep-open-pause=no
fi -vo=gpu

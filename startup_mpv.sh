#!/bin/sh

nrow=`pgrep 'IINA' | wc -l`
if [ $nrow -ge 1 ]; then
    echo 'alread active'
else 
    iina video/BLACK.mp4 --mpv-input-ipc-server=/tmp/mpvsocket --mpv-keep-open-pause=no
fi

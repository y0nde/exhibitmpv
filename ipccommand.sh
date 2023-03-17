#!/bin/sh
echo '{ "command": ["loadfile", "video/WBC.mp4"] }' | nc -U /tmp/socket

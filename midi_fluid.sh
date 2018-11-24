#!/bin/bash

#midi program for connecting Tx/Rx to Fluidsynth
tmux start-server
tmux new-session -d -s my_midi -n runstuff
tmux new-window -t my_midi:1 -n otherstuff

tmux send-keys -t my_midi:0 "/home/pi/nostalgia/nostalgia_fluid/nostalgia /home/pi/nostalgia/nostalgia_fluid/sf2/VintageDreamsWaves-v2.sf2" C-m
tmux send-keys -t my_midi:1 "ttymidi -s /dev/ttyAMA0 -b 38400 &"  C-m
sleep 3
tmux send-keys -t my_midi:1 "aconnect 128:0 129:0" C-m

tmux select-window -t my_midi:runstuff
#tmux attach-session -t my_midi

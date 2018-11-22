#!/bin/bash

tmux start-server

tmux new-session -d -s my_midi -n fluidsynth

tmux new-window -t my_midi:1 -n ttymidi

tmux send-keys -t my_midi:0 "fluidsynth -a alsa -m alsa_seq /usr/share/sounds/sf2/FluidR3_GM.sf2" C-m

sleep 14

#use your specific port settings to connect ttymidi out to Fluidsynth

tmux send-keys -t my_midi:1 "aconnect 128:0 129:0" C-m

tmux select-window -t my_midi:fluidsynth

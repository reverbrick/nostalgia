#==================================
#= Playable Electronics Nostalgia =
#= Hybrid Multi-sample Instrument =
#=     v1.0 2018 Daniel Górny     =
#==================================

Based on wonderful work of:
FLUIDSYNTH author and maintainers (GNU/GPL) http://www.fluidsynth.org/
SunVoX Lib author and maintainers http://warmplace.ru
TTYmidi author and maintainers (GPL) http://www.varal.org/ttymidi/
RTmidi author and maintainers

# instalation in RaspianLite - Stretch
Put utils/config.txt onto boot partition
git clone https://github.com/reverbrick/nostalgia.git
cd nostalgia/utils
make install

#setup uart
enable_uart=1

#setup midiuart
dtoverlay=pi3-miniuart-bt
dtoverlay=midi-uart0

#setup realtime priority

#setup wifi

#setup ssh
sudo touch /boot/ssh

#last step - make it readonly
https://learn.adafruit.com/read-only-raspberry-pi/overview

# todo
Create buildroot for rpi and nanopineo

# sources of ideas
https://learn.adafruit.com/raspberry-pi-zero-creation/enable-uart
https://www.raspberrypi.org/documentation/configuration/uart.md
https://www.instructables.com/id/PiMiDi-A-Raspberry-Pi-Midi-Box-or-How-I-Learned-to/
https://github.com/MarquisdeGeek/FluidPi
https://raspberrypi.stackexchange.com/questions/83610/gpio-pinout-orientation-raspberypi-zero-w
https://openenergymonitor.org/forum-archive/node/12412.html

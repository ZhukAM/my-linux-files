# set monitor mode
airmon-ng
airmon-ng check kill
ip link set wlan0 down
iw dev wlan0 set type monitor
ip link set wlan0 up
iw wlan0 set txpower fixed 3000
iw wlan0 info




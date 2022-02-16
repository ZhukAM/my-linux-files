#set managed mode
airmon-ng
airmon-ng check kill
ip link set wlan0 down
iw dev wlan0 set type managed
ip link set wlan0 up
#service network-manager restart
sudo systemctl enable NetworkManager
sudo systemctl start NetworkManager
iw wlan0 info

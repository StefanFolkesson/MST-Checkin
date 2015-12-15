# RFID
Project: Makerspace Tools: Checkin (MST-Checkin)
Module: RFID
Description: Reads RFID-tags.

##Installation
###Dependensies
* python-serial
* RPI.GPIO

###Enable UART
By default Raspberry Pi uses the UART as a serial console to an external terminal. So we need to turn of this to make use of the UART in bifrost_python.

(Instructions from http://www.raspberry-projects.com/pi/pi-operating-systems/raspbian/io-pins-raspbian/uart-pins)

1. Backup /boot/cmdline.txt
2. Edit /boot/cmdline.txt
3. Remove "console=ttyAMA0,115200" and save
4. Edit /etc/inittab
5. Comment out any line with "ttyAMA0" 
6. Reboot



# CutieBot
Control CutieBot and take pictures via an NES Controller from anywhere in the world!

Developers:
Andrew Nava-Juarez anava014@ucr.edu
Rachel Law rlaw001@ucr.edu

CutieBot Moving: https://www.youtube.com/watch?v=7OSnLsGKe2U&feature=youtu.be CutieBot Vision: https://www.youtube.com/watch?v=d_xMnEGmxv8&feature=youtu.be

Inspiration

We wanted to be able to control our little CutieBot with an NES Controller. And then we wanted it to have a camera. With LIVESTREAM VIDEO! And to be able to take pictures at the push of a button Not only that, we wanted to be able to control it from anywhere else, so we used a Web Server

How it works

We send the Serial information from an NES Controller to an Intel Galileo Board. The Intel Galileo Board transmits the information via HTTP Requests to our online Web Server. A Raspberry Pi sends HTTP Requests to our Web Server in order to get the information about the NES Controller command. The Raspberry Pi processes the data in Python and sends commands to an Arduino Uno. The Arduino Uno that is hooked up to the Raspberry Pi receives data from the Pi and sends over the signals to control the CutieBot motors and camera.

Built With

c
php
python
raspberry-pi
robot
arduino-uno
nes-controller
intel-galileo-board

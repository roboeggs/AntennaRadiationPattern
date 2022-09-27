# Antenna radiation pattern on ESP8266.
This installation was developed for experimental purposes.
ESP №1 acts as a client that is connected to ESP №2.
ESP №1 is installed on the installation and has a reed switch connected to its pin.
The reed switch is used to measure the passage time of each step.
After measuring the data, the data is sent over a TCP connection to ESP №2.
The received data is received by a program developed in Python and shows a directional diagram.

![alt text](https://github.com/roboeggs/AntennaRadiationPattern/blob/main/images/chart.jpg)

Installation model

![Image text](https://github.com/roboeggs/AntennaRadiationPattern/blob/main/images/installation.jpg)

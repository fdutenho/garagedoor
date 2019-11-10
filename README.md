# garagedoor
> Control you garage door with your mobile phone

To do you you connect your garage door's push button via a relay to a nodeMCU.
The nodeMCU connects to our home WiFi and runs a web server. You can reach this web server from your mobile inside your home WiFi.

## 1. preparation
### hardware requirements
You need the following hardware
* 1x nodeMCU
* 1x Relay (3v-5v Relay)
* 1x 230V/5V power
* 1x USB cable (to power the nodeMCU)
* 3x 5v cable (to connect the relay with the nodeMCU)
* 2x 1.5mm² to connect the realy with the garagedoor's push button
* optional: mount, screw and screw nut (M3)

### prepare code
Before you compile the code you have to add a `passwd.h` file to the folder and add two lines.

`garage.ino` includes this file (see line 18: `#include "passwd.h"`).
`passwd.h` itself is not included in this GIT repo (see `.gitignore`) as I do not want to expose the credentials of my Wifi at home ;-)

Add the folowon two lines to `passwd.h` and replace the "..." with your Wifi SSID and password.

```c
const char* ssid = "...";
const char* password = "...";
```

## 2. mount the hardware

### development phase

1. Connect the `3V` and `GND` from the nodeMCU with the `-` and `+` of the relay.
1. Connect the `D0` of the nodeMCU to the `S` (signal) of the relay.
1. During development you will use the USB cable to connect the nodeMCU to your computer.

![front view](front.jpg "front view")
![rear veiew](back.jpg "rear view")

### operations mode
Unplug the nodeMCU from your computer. Carry it to your garage and find a place with access to 230V and the push button that opens your garage (at least it's cable).

1. Use an AC/DC power adapter and a USB cable to empower the nodeMCU.
1. connect the relay to your garage door's push button. Use the `NO` (normally open) and the `COM` ports of the relay. If you hit the "open" button with your mobile device the app will close the port for a few miliseconds and opens it again (same befavior as you pushing the push button).

I'd recommend to connect the relay in parallel to the push button. So you can use both to open/close the door fo your garage.

## 3. use it
> Open the following link in a web brower of a device in the same WiFi than the nodeMCU
> http://garage/


If you do not like this hostname check line 23 of `gargage.ino` and change it.
```c
const char* WiFi_hostname = "garage";
```

# credits & thanks
Thanks to Sarah Ali, her code and blog helped a lot to speed up this project (see http://onlineshouter.com/how-to-control-a-relay-from-a-web-page-with-nodemcu/)

Thanks to the one who made the "remote" image available for re-use on Wikimedia Commons (see https://commons.wikimedia.org/wiki/File:Ic_settings_remote_48px.svg).

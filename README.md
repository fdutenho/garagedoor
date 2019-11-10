# garagedoor
control garage door via nodeMCU and a relay

## prepare
Before you compile the code you have to add a `passwd.h` file to the folder and add two lines.

`garage.ino` includes this file (see line 18: `#include "passwd.h"`).
`passwd.h` itself is not included in this GIT repo (see `.gitignore`) as I do not want to expose the credentials of my Wifi at home ;-)

Add the folowon two lines to `passwd.h` and replace the "..." with your Wifi SSID and password.

```c
const char* ssid = "...";
const char* password = "...";
```

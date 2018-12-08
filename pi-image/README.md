# ChessComputer-Raspberry Pi image
Raspberry Pi image for Chess Challenger 2018

## Image Log
* Using raspbian-stretch-lite (2018-11-13)
### Changes
* Added polyglot-modded
* Added stockfish 10 "general-32" build
* Added git
* Added i2c-tools
* Added ChessComputer-src (compiled ~/chess/)
* Added Opening book (~/chess/)
* Added Polyglot.ini (~/chess/)
* Added startup service
* Added adafruit readonly-fs script

### Setup
Flash the SD card with the pi image using Etcher or something similar.

### Wifi
Open up "wpa_supplicant.conf" and edit it for your home wifi network.
```
network={
   ssid="WIFI"
   psk="PASSWORD"
}
```
After that, copy this file to the root directory of the SD card.

### First Boot
Upon first boot there are a few things to do, after it unpacks itself (ETA 2min). Once the Pi is on the network, ssh into it.
```
username: pi
password: raspberry
```
After that your going to want to stop the chessChallenger service
```
sudo systemctl stop chess.service
```
Once that is done your ready to make the file system read-only. This is because the hardware will NOT gracefully shutdown upon power loss.

### Read-only Setup
navigate to the "readonly-fs" directory.
```
cd ~/readonly-fs/
```
Once there, execute the script
```
sudo ./read-only-fs.sh
```
when prompted, 
* The GPIO pin for read/write jumper is on GPIO21, its soldered on board.
* No need for the halt utility
* Turn the watchdog on

### Rebooting
```
sudo reboot
```
Upon reboot everything should be up and running, it should take a good 20 seconds for the ChessCahllenger splash to appear on the display.

### Finished
Once you verify everything is working properly your good to go kick some ass with ChessChallenger. Powering down the hardware with the on board switch is perfectly fine once the pi is in read-only mode.

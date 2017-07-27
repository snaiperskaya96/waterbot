#### Have a look at this [article](https://blog.skayahack.com/building-a-watering-bot/) to have a general overview about WaterBot and what it does.

Dependencies
------------
  - cmake
  - make
  - g++
  - wiringPi
  - libcurl4-openssl-dev

Command Line Arguments
----------------------
  - `-daemon` Run WaterBot as a daemon
  - `--generate-config [path]` Generates a WaterBot.ini config in the
  specified [path] (Current directory if empty)
  - `--config [file]` Uses the specified [file] as config. While daemon
  it will always look at `/etc/WaterBot/WaterBot.ini`

Build
-----
Make sure you have all the dependencies installed:

```bash
sudo apt update && sudo apt install -y cmake g++ wiringpi libcurl4-openssl-dev
```

Then clone & compile this repository
```bash
git clone https://github.com/snaiperskaya96/waterbot.git WaterBot
cd WaterBot; mkdir build; cd build; cmake ..
make
sudo make install
```

Config your setup by having a look at `/etc/WaterBot/WaterBot.ini`, it
should be quite intuitive.

(You can also generate a brand new config using `Waterbot --generate-config`)

Run WaterBot by either:
```bash
#If `--config` is not specified, WaterBot will look for a WaterBot.ini in the current folder
WaterBot --config /etc/WaterBot/WaterBot.ini
```
as a daemon:
```bash
#Will always use /etc/WaterBot/WaterBot.ini when started as daemon
WaterBot -daemon
```
as a systemd service:
```bash
sudo systemctl start waterbot
```

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
  it will always look at `/etc/WaterBot.ini`
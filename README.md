# PandaPi is a software for 3D printer
##  Use Raspberry Pi as a brain that run the Marlin&Octoprint on Raspberry Pi directly. Improve print speed and smoothness
### Standing on the shoulders of giants, there will be more possibilities in the 3D printing world.
If you want to run PandaPi on RPi, you need one following hardware board that can be droppd in creality Ender3 printer with this shield+Raspberry Pi ,just need to print one case for it.

![](https://raw.githubusercontent.com/markniu/PandaPi/master/doc/main_octo.jpg)

1. High process speed.

2. Octoprint + marlin.

3. Easy to edit/compile/run (use web browser to edit instead of Arduino IDE/platformio)

* ##  FAQ：
1. what's the difference from Klipper

    PandaPi: use RPi to control 3D printer directly,except the temperature control which is just to maintain the temperature.

    Klipper: uses a RPi to parse G-code,map out curves,set accelerations,and then send the motor command to the MCU via uart.

2. Why is there a mcu?

   RPi has not enough GPIO pin for handle all the motors,hotend,bed,endstop,LCD,auto bed level,run out sensor.

3. how do this assure the real time control?

   about the real-time, I did a [test](https://hackaday.io/project/166466-3dprinter-firmware-run-on-raspberrypi/log/167122-upgrade-to-real-time-linux) . it is not real time actually,but we guarantee motor coordination. and the RPi is more than fast enough that it is not a problem.and I test it with pi4 the cpu speed is quickly than pi3! BTW I test it with all the function like camera octoprint,they are used a lot of RAM but little CPU.

* ##   [Guides link](https://github.com/markniu/PandaPi/wiki) 


* ## Hardware resources v1.0 
RaspberryPi | Pi 4B/3B/3B+  | .
--- | --- | --- 
Extruders | 	1 | 	 
Controlled Fans | 	3	 |  1 board self controlled
Heaters   | 	2	 |  
Endstops   | 	3	 | 
Temp sens   | 	2	 |  100K NTC (thermal resistance)	
SWD   | 	1	 | STlinkV2
Serial port chip   | 	CH340G	 | 
stepper driver   |  4*(TMC2209/TMC2208/A4988/TMC2130)	 | Modular, replaceable,no uart/SPI
Input   | 	7~35V 20A max	 | 
heater Output   | 	15Amax	 | 
MCU   | 	stm32	 |  
LCD   | 	Graphic128*64/LCD2004	 | 
on board FAN   | 	silent 24V self auto controlled	 | 
Spacer screw   | 	Nylon spacer screw	 | 
filament detect pin    | 	  reuse the SWD pin   | 	
Bed leveling    | 	  BLtouch  | 	

* ## Block diagram
![Opensource](https://raw.githubusercontent.com/markniu/PandaPi/master/doc/dlg.png)

* ##   [Case for ender3](https://www.thingiverse.com/thing:3857748) 
![Opensource](https://raw.githubusercontent.com/markniu/PandaPi/master/doc/65609.jpg)

![Opensource](https://raw.githubusercontent.com/markniu/PandaPi/master/doc/lion.jpg)

[youtube](https://www.youtube.com/channel/UCXq9t12N4FJ8aEGx7SY5bcA) 

* ###  Facebook support

<a href="https://www.facebook.com/groups/380795976169477/"><img src="https://raw.githubusercontent.com/markniu/PandaPi/master/doc/Facebook.png" alt="facebook group" width="100" height="100"></a>

* ##  where to buy?
<a href="https://www.tindie.com/stores/niujl123/?ref=offsite_badges&utm_source=sellers_niujl123&utm_medium=badges&utm_campaign=badge_medium"><img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-mediums.png" alt="I sell on Tindie" width="150" height="78"></a>

[Tindie](https://www.tindie.com/products/17947/)  






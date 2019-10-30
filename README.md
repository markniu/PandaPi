# PandaPi for 3D printer
##  use Raspberry Pi as brain, Integrates Marlin & Octoprint into the Raspberry Pi. Improve print speed and smoothness
### Standing on the shoulders of giants, there will be more possibilities in the 3D printing world.


![](https://raw.githubusercontent.com/markniu/PandaPi/master/doc/main_octo.jpg)

1. High process speed.

2. Octoprint + marlin.

3. Easy to edit/compile/run (use web browser to edit instead of Arduino IDE/platformio)


##   ![Guides link](https://github.com/markniu/PandaPi/wiki) 


## Hardware resources v1.0 
you can drop in creality Ender3 printer with this shield+Raspberry Pi ,just need to print one case for it.

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

## Block diagram
![Opensource](https://raw.githubusercontent.com/markniu/PandaPi/master/doc/dlg.png)

## Case for ender3 
![Opensource](https://raw.githubusercontent.com/markniu/PandaPi/master/doc/case.jpg)


[youtube](https://www.youtube.com/channel/UCXq9t12N4FJ8aEGx7SY5bcA)     [facebook](https://www.facebook.com/groups/380795976169477/)

## where to buy?
<a href="https://www.tindie.com/stores/niujl123/?ref=offsite_badges&utm_source=sellers_niujl123&utm_medium=badges&utm_campaign=badge_medium"><img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-mediums.png" alt="I sell on Tindie" width="150" height="78"></a>

[Tindie](https://www.tindie.com/products/17947/) The 50 pcs will be arrived November 1st .






## 64-bit 3D printer controller.                                             
 Run Marlin & Octoprint on Raspberry Pi directly.             ([Where to buy and support me](https://www.pandapi3d.com/))
### Software   
1. ###  better prints at faster speeds
     If you want to do more higher speed or print some short line or corner the higher process speed is very important,otherwise there will be some slight on the surface. so 32 bit MCU is better,but if you want add more function like web camera,HDMI LCD... little space,for friendly easy to use this PandaPi runs on the powerful Raspberry Pi is the best. 
2. ### Octoprint + marlin.
    the marlin code is very stable and are familiar with us, if we have a good idea or control algorithm, we can change it easily.   
3. ### No arduino, no platformIO.
    configure your printer with browser
    
### Hardware    
1. ####  Support mixed use of 3V-24V fans
2. ####  optocoupler for bed proximity sensor
3. ####  Low temperature mosfet at high current heating.
4. ####  autorecovery fuses and isolation components for over-current and reverse polarity protection for board,drivers,raspberry pi.
5. ####  no wiring for TMC driver sensorless homing and uart mode.


<img width="1000"  src="https://gitee.com/markyue/pandapi_wiki/raw/master/imges/V28/407172250.jpg"/> 

If you want to run PandaPi on RPi, you need one PandaPi extra board that can be droppd in creality Ender3 printer with this board+Raspberry Pi ,just need to print one case for it.
<img  width="550"  src="https://gitee.com/markyue/pandapi_wiki/raw/master/imges/60202.jpg"/>


* ##   [Hardware resources](https://github.com/markniu/PandaPi/wiki/Hardware-resources) 



RaspberryPi | Pi 4B/3B/3B+  | .
--- | --- | --- 
Extruders | 	2 | 	 
Controlled Fans | 	3	 |  FAN0:hotend cooler,it will be opened if the temperature is higher than 60°C.FAN1:model cooler, controlled by the gcode file or gcode command, M106: Set Fan Speed "M106 S255", M107: Fan Off.FAN2:board cooler,If the driver is working, it will be opened.
Heaters   | 	3	 |  
Endstops   | 	3	 | 
Temp sens   | 	3	 |  100K NTC (thermal resistance)	
SWD   | 	1	 | STlinkV2
Serial port chip   | 	CH340G	 | 
stepper driver   |  6*(TMC2209/TMC2208/A4988)	 | Modular, replaceable,uart for TMC2209 sensorless endstop
Input   | 	9~28V 20A max	 | power both the board and the Raspberry Pi
heater Output   | 	15Amax	 | 
MCU   | 	stm32	 |  
LCD   | 	LCD128*64/HDMI/PandaTouchScreen	 | 
FAN   |   Support mixed use of 3V-24V fans   | 
Spacer screw   | 	Nylon spacer screw	 | 
filament detect pin    | 	  reuse the SWD pin   | 	
Bed leveling    | 	  BLtouch  | 	 support wild range voltage 5V~36V Inductive sensor NPN, since it have optocoupler.
Protection    | 	 4 autorecovery fuses and isolation components  | 	 on board for over-current and reverse polarity protection for board,drivers,raspberry pi.

* ## Block diagram
<img width="450" src="https://gitee.com/markyue/pandapi_wiki/raw/master/imges/dlg2.png"/>

* ##   [Guides](https://github.com/markniu/PandaPi/wiki) 
**Quick start guide**：
 
* [Flashing RaspberrPi img](https://github.com/markniu/PandaPi/wiki/How-to-Flash-img-&-WIFI-setup)

* [Wiring](https://github.com/markniu/PandaPi/wiki/How-to-wire)

[**Advanced topics**](https://github.com/markniu/PandaPi/wiki)




* ##  FAQ：
1. what's the difference from Klipper

    PandaPi: use RPi to control 3D printer directly,except the temperature control which is just to maintain the temperature.

    Klipper: uses a RPi to parse G-code,map out curves,set accelerations,and then send the motor command to the MCU via uart.

     the obvious difference is that PandaPi control the motor directly.the gpio on the RPi speed being able to signal at 10+ Mhz as compared to 8/32bit MCU limit of about 10Khz/200khz for steps.that is one of my reason to explore this project. although the <100Khz speed is enough for our FDM printer recently but not the future.

2. Why is there a mcu?

   RPi has not enough GPIO pin for handle all the motors,hotend,bed,endstop,LCD,auto bed level,run out sensor.

3. how do this assure the real time control?

   about the real-time, here is the result that is almost perfect for real time control drivers. the output signal of the one raspberryPI's GPIO,and displayed by the oscilloscope.
<img  width="750"  src="https://gitee.com/markyue/pandapi_wiki/raw/master/imges/60632064_o.jpg"/>

## [Join Facebook](https://www.facebook.com/groups/380795976169477/)

<img width="1024"  src="https://gitee.com/markyue/pandapi_wiki/raw/master/imges/V28/2192018.png"/> 

## [Where to buy](https://www.pandapi3d.com/)  
thanks for your support! and have fun with 3D printer world!






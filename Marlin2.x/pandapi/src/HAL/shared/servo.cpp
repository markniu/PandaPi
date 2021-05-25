/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

/**
 * servo.cpp - Interrupt driven Servo library for Arduino using 16 bit timers- Version 2
 * Copyright (c) 2009 Michael Margolis.  All right reserved.
 */

/**
 * A servo is activated by creating an instance of the Servo class passing the desired pin to the attach() method.
 * The servos are pulsed in the background using the value most recently written using the write() method
 *
 * Note that analogWrite of PWM on pins associated with the timer are disabled when the first servo is attached.
 * Timers are seized as needed in groups of 12 servos - 24 servos use two timers, 48 servos will use four.
 *
 * The methods are:
 *
 * Servo - Class for manipulating servo motors connected to Arduino pins.
 *
 * attach(pin)           - Attach a servo motor to an i/o pin.
 * attach(pin, min, max) - Attach to a pin, setting min and max values in microseconds
 *                         Default min is 544, max is 2400
 *
 * write()               - Set the servo angle in degrees. (Invalid angles —over MIN_PULSE_WIDTH— are treated as µs.)
 * writeMicroseconds()   - Set the servo pulse width in microseconds.
 * move(pin, angle)      - Sequence of attach(pin), write(angle), safe_delay(servo_delay[servoIndex]).
 *                         With DEACTIVATE_SERVOS_AFTER_MOVE it detaches after servo_delay[servoIndex].
 * read()                - Get the last-written servo pulse width as an angle between 0 and 180.
 * readMicroseconds()    - Get the last-written servo pulse width in microseconds.
 * attached()            - Return true if a servo is attached.
 * detach()              - Stop an attached servo from pulsing its i/o pin.
 */

#include "../../inc/MarlinConfig.h"

#if SHARED_SERVOS

#include "servo.h"

//  PANDAPI
//#include "servo_private.h"

#include "wiringPi.h"
#include "wiringPiI2C.h"
extern int i2c_fd ;  

//ServoInfo_t servo_info[MAX_SERVOS];             // static array of servo info structures
uint8_t ServoCount = 0;                         // the total number of attached servos

#define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo
#define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a servo
#define DEFAULT_PULSE_WIDTH  1500     // default pulse width when servo is attached
#define REFRESH_INTERVAL    20000     // minimum time to refresh servos in microseconds

#define SERVO_MIN(v) (MIN_PULSE_WIDTH - (v) * 4) // minimum value in uS for this servo
#define SERVO_MAX(v) (MAX_PULSE_WIDTH - (v) * 4) // maximum value in uS for this servo

/************ static functions common to all instances ***********************/
#if 0

static boolean isTimerActive(timer16_Sequence_t timer) {
  // returns true if any servo is active on this timer
  LOOP_L_N(channel, SERVOS_PER_TIMER) {
    if (SERVO(timer, channel).Pin.isActive)
      return true;
  }
  return false;
}
#endif 

/****************** end of static functions ******************************/

Servo::Servo() {
#if 0
  if (ServoCount < MAX_SERVOS) {
    servoIndex = ServoCount++;                    // assign a servo index to this instance
    servo_info[servoIndex].ticks = usToTicks(DEFAULT_PULSE_WIDTH);   // store default values  - 12 Aug 2009
  }
  else
    servoIndex = INVALID_SERVO;  // too many servos
#endif  
}

int8_t Servo::attach(const int inPin) {
  return attach(inPin, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
}

int8_t Servo::attach(const int inPin, const int inMin, const int inMax) {
#if 0
  if (servoIndex >= MAX_SERVOS) return -1;

  if (inPin > 0) servo_info[servoIndex].Pin.nbr = inPin;
  pinMode(servo_info[servoIndex].Pin.nbr, OUTPUT); // set servo pin to output

  // TODO: min/max check: ABS(min - MIN_PULSE_WIDTH) / 4 < 128
  min = (MIN_PULSE_WIDTH - inMin) / 4; //resolution of min/max is 4 uS
  max = (MAX_PULSE_WIDTH - inMax) / 4;

  // initialize the timer if it has not already been initialized
  timer16_Sequence_t timer = SERVO_INDEX_TO_TIMER(servoIndex);
  if (!isTimerActive(timer)) initISR(timer);
  servo_info[servoIndex].Pin.isActive = true;  // this must be set after the check for isTimerActive
#endif
  return servoIndex;
}

void Servo::detach() {
#if 0	
  servo_info[servoIndex].Pin.isActive = false;
  timer16_Sequence_t timer = SERVO_INDEX_TO_TIMER(servoIndex);
  if (!isTimerActive(timer)) finISR(timer);
#endif  
}
inline long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Servo::write(int value) {
#if PANDAPI	
	printf("Servo::write\n");

	if (value < MIN_PULSE_WIDTH) { // treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds)
	  value = map(constrain(value, 0, 180), 0, 180, 544, 2400);
	//  TIM_SetCompare2(TIM1, value); //

	////////////////
	char tmp_data[32],cmd_buf[64];
	int cn=0;
	sprintf(tmp_data,"P%d;",value);
	printf(tmp_data);printf("\n");
	for(int i=0;i<strlen(tmp_data);i++)
	wiringPiI2CWriteReg8(i2c_fd, 8, tmp_data[i]);
	//wiringPiI2CWriteReg8(i2c_fd, 8, ';');
	unsigned int kk=millis();
	while((cmd_buf[cn++]=wiringPiI2CReadReg8(i2c_fd,8))!='\0')
	{
	  delay(0);
	  if((millis()-kk)>2000)
		break;
	  if(cn>=64) break;
	}
	printf(cmd_buf);
	printf("\n");
	///////////////////
	}
#else
  if (value < MIN_PULSE_WIDTH)    // treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds)
    value = map(constrain(value, 0, 180), 0, 180, SERVO_MIN(min), SERVO_MAX(max));
  writeMicroseconds(value);
 #endif
}

void Servo::writeMicroseconds(int value) {
#if 0	
  // calculate and store the values for the given channel
  byte channel = servoIndex;
  if (channel < MAX_SERVOS) {  // ensure channel is valid
    // ensure pulse width is valid
    value = constrain(value, SERVO_MIN(min), SERVO_MAX(max)) - (TRIM_DURATION);
    value = usToTicks(value);  // convert to ticks after compensating for interrupt overhead - 12 Aug 2009

    CRITICAL_SECTION_START();
    servo_info[channel].ticks = value;
    CRITICAL_SECTION_END();
  }
#endif  
}

// return the value as degrees
int Servo::read() {

return map(readMicroseconds() + 1, SERVO_MIN(min), SERVO_MAX(max), 0, 180);
}

int Servo::readMicroseconds() {
#if 0
  return (servoIndex == INVALID_SERVO) ? 0 : ticksToUs(servo_info[servoIndex].ticks) + (TRIM_DURATION);
#endif
}

bool Servo::attached() { 
#if 0	
	return servo_info[servoIndex].Pin.isActive;
#endif
	}

void Servo::move(const int value) {
  constexpr uint16_t servo_delay[] = SERVO_DELAY;
  static_assert(COUNT(servo_delay) == NUM_SERVOS, "SERVO_DELAY must be an array NUM_SERVOS long.");
  if (attach(0) >= 0) {
    write(value);
    safe_delay(servo_delay[servoIndex]);
    TERN_(DEACTIVATE_SERVOS_AFTER_MOVE, detach());
  }
}

#endif // SHARED_SERVOS

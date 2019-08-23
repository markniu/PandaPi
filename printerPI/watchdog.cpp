/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "Marlin.h"
//#include "stm32f4xx_iwdg.h"


#if ENABLED(USE_WATCHDOG)

#include "watchdog.h"

// Initialize watchdog with 8s timeout, if possible. Otherwise, make it 4s.
void watchdog_init() {

#if 0//PANDAPI
// Tout=((4*2^prer)*rlr)/40 (ms).

#define LSI_FREQ   40000/16//40000/32

 /*Enables write access to IWDG_PR and IWDG_RLR registers */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    /*Set prescaler value*/
    IWDG_SetPrescaler(IWDG_Prescaler_64);
    /*Set reload value
    Counter Reload Value = 250ms/IWDG counter clock period
                          = 250ms / (LSI/32)
                          = 0.25s / (LsiFreq/32)
                          = LsiFreq/(32 * 4)
                          = LsiFreq/128
   */
    IWDG_SetReload(LSI_FREQ);
    /*Download reload value to register*/
    IWDG_ReloadCounter();
	IWDG_Enable();


#endif
  #if ENABLED(WATCHDOG_DURATION_8S) && defined(WDTO_8S)
    #define WDTO_NS WDTO_8S
  #else
    #define WDTO_NS WDTO_4S
  #endif
  #if ENABLED(WATCHDOG_RESET_MANUAL)
    // We enable the watchdog timer, but only for the interrupt.
    // Take care, as this requires the correct order of operation, with interrupts disabled.
    // See the datasheet of any AVR chip for details.
    wdt_reset();
    cli();
    _WD_CONTROL_REG = _BV(_WD_CHANGE_BIT) | _BV(WDE);
    _WD_CONTROL_REG = _BV(WDIE) | (WDTO_NS & 0x07) | ((WDTO_NS & 0x08) << 2); // WDTO_NS directly does not work. bit 0-2 are consecutive in the register but the highest value bit is at bit 5
                                                                              // So worked for up to WDTO_2S
    sei();
    wdt_reset(); 
  #else
 //   wdt_enable(WDTO_NS); // The function handles the upper bit correct.
  #endif
  //delay(10000); // test it!
}

//===========================================================================
//=================================== ISR ===================================
//===========================================================================

// Watchdog timer interrupt, called if main program blocks >4sec and manual reset is enabled.
#if ENABLED(WATCHDOG_RESET_MANUAL)
  ISR(WDT_vect) {
    sei();  // With the interrupt driven serial we need to allow interrupts.
    SERIAL_ERROR_START();
    SERIAL_ERRORLNPGM("Watchdog barked, please turn off the printer.");
    kill(PSTR("ERR:Watchdog")); //kill blocks //up to 16 characters so it fits on a 16x2 display
    while (1); //wait for user or serial reset
  }
#endif // WATCHDOG_RESET_MANUAL

#endif // USE_WATCHDOG

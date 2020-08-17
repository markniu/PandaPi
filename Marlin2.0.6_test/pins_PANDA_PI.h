

#ifndef BOARD_NAME
  #define BOARD_NAME "PANDA,PI"
#endif

#define BOARD_INFO_NAME      "PANDA,PI"



//
// Servos
//

#define SERVO0_PIN       255// 0xBE

//
#define X_MIN_PIN          1 
#define X_MAX_PIN          1 

#define Y_MIN_PIN          4 
#define Y_MAX_PIN          4 

#define Z_MAX_PIN          11 
#define Z_MIN_PIN            11 



#ifndef FIL_RUNOUT_PIN
  #define FIL_RUNOUT_PIN    255
#endif



//
// Z Probe (when not Z_MIN_PIN)
//
//#ifndef Z_MIN_PROBE_PIN
//  #define Z_MIN_PROBE_PIN  7
//#endif

//
// Steppers
//
#define X_STEP_PIN         7 
#define X_DIR_PIN          2 
#define X_ENABLE_PIN       0 

#define Y_STEP_PIN         12 
#define Y_DIR_PIN          5 
#define Y_ENABLE_PIN       0 

#define Z_STEP_PIN         14 
#define Z_DIR_PIN          13 
#define Z_ENABLE_PIN       0 


#define E0_STEP_PIN        10 
#define E0_DIR_PIN         6 
#define E0_ENABLE_PIN      0 

#define E1_STEP_PIN        26
#define E1_DIR_PIN         25
#define E1_ENABLE_PIN      0

#define E2_STEP_PIN        31
#define E2_DIR_PIN         21
#define E2_ENABLE_PIN      0
/*
#define Z2_STEP_PIN        31
#define Z2_DIR_PIN         21
#define Z2_ENABLE_PIN      0
*/

/**
 * Default pins for TMC software SPI
 */

#if HAS_TRINAMIC
  #define X_HARDWARE_SERIAL  customizedSerial1
 //  #define X2_HARDWARE_SERIAL customizedSerial1
  #define Y_HARDWARE_SERIAL  customizedSerial1
 //  #define Y2_HARDWARE_SERIAL customizedSerial1
  #define Z_HARDWARE_SERIAL  customizedSerial1
  // #define Z2_HARDWARE_SERIAL customizedSerial1
  #define E0_HARDWARE_SERIAL customizedSerial1
  //#define E1_HARDWARE_SERIAL customizedSerial1
  //#define E2_HARDWARE_SERIAL customizedSerial1
  //#define E3_HARDWARE_SERIAL customizedSerial1
  //#define E4_HARDWARE_SERIAL customizedSerial1



#endif



//
// Augmentation for auto-assigning RAMPS plugs
//
#if DISABLED(IS_RAMPS_EEB) && DISABLED(IS_RAMPS_EEF) && DISABLED(IS_RAMPS_EFB) && DISABLED(IS_RAMPS_EFF) && DISABLED(IS_RAMPS_SF) && !PIN_EXISTS(MOSFET_D)
  #if HOTENDS > 1
    #if TEMP_SENSOR_BED
      #define IS_RAMPS_EEB
    #else
      #define IS_RAMPS_EEF
    #endif
  #elif TEMP_SENSOR_BED
    #define IS_RAMPS_EFB
  #else
    #define IS_RAMPS_EFF
  #endif
#endif

//
// Heaters / Fans
//
#ifndef MOSFET_D_PIN
  #define MOSFET_D_PIN     -1
#endif

// heat connector index
#define HOTBED_CODE       0  
#define HOTEND_0_CODE     1  
#define HOTEND_1_CODE     2  


#define HEATER_0_PIN     255
#define HEATER_1_PIN     255
#define HEATER_BED_PIN   255
#define TEMP_0_PIN       255
#define TEMP_1_PIN       255
#define TEMP_BED_PIN     255
#define TEMP_BOARD_PIN   255

#define FAN_PIN         255
#define FAN1_PIN         255
#define FAN2_PIN         255
#define FAN3_PIN         255


//////////////////////////
// LCDs and Controllers //
//////////////////////////
#if ENABLED(ULTRA_LCD)
  // LCD Display output pins
  #ifdef REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER
	#define LCD_PINS_RS      28 
	#define LCD_PINS_ENABLE  29 
	#define LCD_PINS_D4      27  
  #endif

	#define SD_DETECT_PIN   255   
   // LCD Display input pins
  #if ENABLED(NEWPANEL)
	#define BEEPER_PIN		24 
	#define BTN_ENC 		30 
	#define BTN_EN1 		22 
	#define BTN_EN2 		23 
  #endif // NEWPANEL

#endif // ULTRA_LCD

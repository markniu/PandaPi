
#ifndef BOARD_NAME
  #define BOARD_NAME "PANDA,PI"
#endif
//
// Servos
//

//#define SERVO0_PIN       2// 0xBE

//
#define X_MIN_PIN           1//0xE5

#define Y_MIN_PIN          4//0xE3
//#define Y_MAX_PIN          //0xBD//0xE2

//#define Z_MAX_PIN          // 0xB8//0xE0

#if ENABLED(BLTOUCH)
#define Z_MIN_PIN          11//0xE1

#else
#define Z_MIN_PIN            11//0xE1

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
#define X_STEP_PIN         7//0xE3//0xC6
#define X_DIR_PIN          2//0xDD
#define X_ENABLE_PIN       0//0xA8//38

#define Z_STEP_PIN        12// 0xAC
#define Z_DIR_PIN         5// 0xAB
#define Z_ENABLE_PIN      0//0XAF

#define Y_STEP_PIN         14// 0xD6
#define Y_DIR_PIN          13//0xD3
#define Y_ENABLE_PIN       0//0xA3


#define E0_STEP_PIN        10//0xB2
#define E0_DIR_PIN         6//0xBB
#define E0_ENABLE_PIN      0//0xC4

//#define E1_STEP_PIN        12
//#define E1_DIR_PIN         12
//#define E1_ENABLE_PIN      12

/**
 * Default pins for TMC software SPI
 */

#if HAS_DRIVER(TMC2208)

#endif

//
// Temperature Sensors
//
//#define TEMP_0_PIN        11//0xB1// 13   // Analog Input
//#define TEMP_1_PIN        11//0xB0   // Analog Input
//#define TEMP_2_PIN        0xC0//0xB0   // Analog Input
//#define TEMP_BED_PIN      11//0xC5   // Analog Input
//#define TEMP_BOARD_PIN        11//0xB0   // Analog Input

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
//#ifndef RAMPS_D8_PIN
//  #define RAMPS_D8_PIN   0xA2//0xC4  // bed pin
//#endif
//#ifndef RAMPS_D9_PIN
//  #define RAMPS_D9_PIN      0xA1
//#endif
//#ifndef RAMPS_D10_PIN
//  #define RAMPS_D10_PIN  0xA1// GPIOB+GPIO_Pin_0  heater pin
//#endif

#define HEATER_0_PIN     26
#define HEATER_BED_PIN  26//0xD0
#define TEMP_0_PIN     25
#define TEMP_BED_PIN      25
#define TEMP_BOARD_PIN  25

/*

#if EXTRUDERS > 1
#define HEATER_1_PIN     10
#endif
#define FAN_PIN         10
#define FAN1_PIN        14
#define FAN2_PIN        11
#define FAN3_PIN        12
#define FAN4_PIN        17

#define FAN_SOFT_PWM
#if ENABLED(IS_RAMPS_EFB)                      // Hotend, Fan, Bed


#elif ENABLED(IS_RAMPS_EEF)                    // Hotend, Hotend, Fan

  #define HEATER_1_PIN   RAMPS_D9_PIN
  #define FAN_PIN        RAMPS_D8_PIN
#elif ENABLED(IS_RAMPS_EEB)                    // Hotend, Hotend, Bed
  //#define HEATER_1_PIN     RAMPS_D9_PIN
  //#define HEATER_BED_PIN   RAMPS_D8_PIN
#elif ENABLED(IS_RAMPS_EFF)                    // Hotend, Fan, Fan
  #define FAN1_PIN         RAMPS_D8_PIN
#elif DISABLED(IS_RAMPS_SF)                    // Not Spindle, Fan (i.e., "EFBF" or "EFBE")
  #define HEATER_BED_PIN   RAMPS_D8_PIN
  #if HOTENDS == 1
    #define FAN1_PIN       MOSFET_D_PIN
  #else
    #define HEATER_1_PIN   MOSFET_D_PIN
  #endif
#endif

#ifndef FAN_PIN
  #if ENABLED(IS_RAMPS_EFB) || ENABLED(IS_RAMPS_EFF)  // Hotend, Fan, Bed or Hotend, Fan, Fan
    #define FAN_PIN        RAMPS_D9_PIN
  #elif ENABLED(IS_RAMPS_EEF) || ENABLED(IS_RAMPS_SF) // Hotend, Hotend, Fan or Spindle, Fan
    #define FAN_PIN        RAMPS_D8_PIN
  #elif ENABLED(IS_RAMPS_EEB)                         // Hotend, Hotend, Bed
    #define FAN_PIN         4   // IO pin. Buffer needed
  #else                                               // Non-specific are "EFB" (i.e., "EFBF" or "EFBE")
    #define FAN_PIN        RAMPS_D9_PIN
  #endif
#endif

//
// Misc. Functions
//
//
#define LED_PIN            13

#ifndef FILWIDTH_PIN
  #define FILWIDTH_PIN      5   // Analog Input on AUX2
#endif

// define digital pin 4 for the filament runout sensor. Use the RAMPS 1.4 digital input 4 on the servos connector
#ifndef FIL_RUNOUT_PIN
  #define FIL_RUNOUT_PIN    4
#endif

#ifndef PS_ON_PIN
  #define PS_ON_PIN        12
#endif
*/

//
// M3/M4/M5 - Spindle/Laser Control
//


//
// Průša i3 MK2 Multiplexer Support
//
/*#ifndef E_MUX0_PIN
  #define E_MUX0_PIN 40   // Z_CS_PIN
#endif
#ifndef E_MUX1_PIN
  #define E_MUX1_PIN 42   // E0_CS_PIN
#endif
#ifndef E_MUX2_PIN
  #define E_MUX2_PIN 44   // E1_CS_PIN
#endif
*/
//////////////////////////
// LCDs and Controllers //
//////////////////////////

#if ENABLED(ULTRA_LCD)

  //
  // LCD Display output pins
  //
  #if ENABLED(REPRAPWORLD_GRAPHICAL_LCD)



  #else

    #if ENABLED(CR10_STOCKDISPLAY)



    #else

      #if ENABLED(MKS_12864OLED) || ENABLED(MKS_12864OLED_SSD1306)
 /*       #define LCD_PINS_DC     25   // Set as output on init
        #define LCD_PINS_RS     27   // Pull low for 1s to init
        // DOGM SPI LCD Support
        #define DOGLCD_CS       16
        #define DOGLCD_MOSI     17
        #define DOGLCD_SCK      23
        #define DOGLCD_A0       LCD_PINS_DC
        */
      #else //stm32
	  	#ifdef REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER
	        #define LCD_PINS_RS     28//0xEE//0xC6// 0xDA//0xE6 //T_PEN
	        #define LCD_PINS_ENABLE  29//0xBA//0xEF //D11
	        #define LCD_PINS_D4       27 //0xC8 //D19
        #else
		/*	#define LCD_PINS_RS     5//0xEE //T_PEN
	        #define LCD_PINS_ENABLE 12 //D11
	        #define LCD_PINS_D4     13 //D13
	        #define LCD_PINS_D5     14//0xED //D14
	        #define LCD_PINS_D6     12 //D15
			#define LCD_PINS_D7     14//D12
*/
		#endif

		
       //
		 ///////////////////
 /*  #define SD_DETECT_PIN   31 // 0xC7//49
   #define SD_SPI_SCK	30//0xA5//
   #define SD_SPI_MISO	 30// 0xA6
   #define SD_SPI_MOSI	 31//0xA7
   #define SD_SPI_CS   30//0xA4
//   #define SD_SPI_REMAP  30 
   #define SD_SPI_NUM	1
		/////////////////////////////  
   #define SDSS               SD_SPI_CS//53	 */
/////////


////////
      #endif

     // 

      #if DISABLED(NEWPANEL)
 //        #define BEEPER_PIN      20
		 
      #endif

    #endif

    #if DISABLED(NEWPANEL)
      // Buttons are attached to a shift register
      // Not wired yet
      //#define SHIFT_CLK       38
      //#define SHIFT_LD        42
      //#define SHIFT_OUT       40
      //#define SHIFT_EN        17
    #endif

  #endif

  //
  // LCD Display input pins
  //
  #if ENABLED(NEWPANEL)
   #define BEEPER_PIN		 24// 0xBD//0xEC
   #define BTN_ENC 		30//0xEF//0xED
 
   #define BTN_EN1 		22//0xE9
   #define BTN_EN2 		23//0xE8

  #endif // NEWPANEL

#endif // ULTRA_LCD



#ifndef BOARD_NAME
  #define BOARD_NAME "PANDA,PI"
#endif
//
// Servos
//

//#define SERVO0_PIN       2// 0xBE

//
#define X_MIN_PIN           1//0xE5

#define Y_MIN_PIN          4//0xE3
//#define Y_MAX_PIN          //0xBD//0xE2

//#define Z_MAX_PIN          // 0xB8//0xE0

#if ENABLED(BLTOUCH)
#define Z_MIN_PIN          11//0xE1

#else
#define Z_MIN_PIN            11//0xE1

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
#define X_STEP_PIN         7//0xE3//0xC6
#define X_DIR_PIN          2//0xDD
#define X_ENABLE_PIN       0//0xA8//38

#define Y_STEP_PIN        12// 0xAC
#define Y_DIR_PIN         5// 0xAB
#define Y_ENABLE_PIN      0//0XAF

#define Z_STEP_PIN         14// 0xD6
#define Z_DIR_PIN          13//0xD3
#define Z_ENABLE_PIN       0//0xA3


#define E0_STEP_PIN        10//0xB2
#define E0_DIR_PIN         6//0xBB
#define E0_ENABLE_PIN      0//0xC4

//#define E1_STEP_PIN        12
//#define E1_DIR_PIN         12
//#define E1_ENABLE_PIN      12

/**
 * Default pins for TMC software SPI
 */

#if HAS_DRIVER(TMC2208)

#endif

//
// Temperature Sensors
//
//#define TEMP_0_PIN        11//0xB1// 13   // Analog Input
//#define TEMP_1_PIN        11//0xB0   // Analog Input
//#define TEMP_2_PIN        0xC0//0xB0   // Analog Input
//#define TEMP_BED_PIN      11//0xC5   // Analog Input
//#define TEMP_BOARD_PIN        11//0xB0   // Analog Input

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
//#ifndef RAMPS_D8_PIN
//  #define RAMPS_D8_PIN   0xA2//0xC4  // bed pin
//#endif
//#ifndef RAMPS_D9_PIN
//  #define RAMPS_D9_PIN      0xA1
//#endif
//#ifndef RAMPS_D10_PIN
//  #define RAMPS_D10_PIN  0xA1// GPIOB+GPIO_Pin_0  heater pin
//#endif

#define HEATER_0_PIN     26
#define HEATER_BED_PIN  26//0xD0
#define TEMP_0_PIN     25
#define TEMP_BED_PIN      25
#define TEMP_BOARD_PIN  25

/*

#if EXTRUDERS > 1
#define HEATER_1_PIN     10
#endif
#define FAN_PIN         10
#define FAN1_PIN        14
#define FAN2_PIN        11
#define FAN3_PIN        12
#define FAN4_PIN        17

#define FAN_SOFT_PWM
#if ENABLED(IS_RAMPS_EFB)                      // Hotend, Fan, Bed


#elif ENABLED(IS_RAMPS_EEF)                    // Hotend, Hotend, Fan

  #define HEATER_1_PIN   RAMPS_D9_PIN
  #define FAN_PIN        RAMPS_D8_PIN
#elif ENABLED(IS_RAMPS_EEB)                    // Hotend, Hotend, Bed
  //#define HEATER_1_PIN     RAMPS_D9_PIN
  //#define HEATER_BED_PIN   RAMPS_D8_PIN
#elif ENABLED(IS_RAMPS_EFF)                    // Hotend, Fan, Fan
  #define FAN1_PIN         RAMPS_D8_PIN
#elif DISABLED(IS_RAMPS_SF)                    // Not Spindle, Fan (i.e., "EFBF" or "EFBE")
  #define HEATER_BED_PIN   RAMPS_D8_PIN
  #if HOTENDS == 1
    #define FAN1_PIN       MOSFET_D_PIN
  #else
    #define HEATER_1_PIN   MOSFET_D_PIN
  #endif
#endif

#ifndef FAN_PIN
  #if ENABLED(IS_RAMPS_EFB) || ENABLED(IS_RAMPS_EFF)  // Hotend, Fan, Bed or Hotend, Fan, Fan
    #define FAN_PIN        RAMPS_D9_PIN
  #elif ENABLED(IS_RAMPS_EEF) || ENABLED(IS_RAMPS_SF) // Hotend, Hotend, Fan or Spindle, Fan
    #define FAN_PIN        RAMPS_D8_PIN
  #elif ENABLED(IS_RAMPS_EEB)                         // Hotend, Hotend, Bed
    #define FAN_PIN         4   // IO pin. Buffer needed
  #else                                               // Non-specific are "EFB" (i.e., "EFBF" or "EFBE")
    #define FAN_PIN        RAMPS_D9_PIN
  #endif
#endif

//
// Misc. Functions
//
//
#define LED_PIN            13

#ifndef FILWIDTH_PIN
  #define FILWIDTH_PIN      5   // Analog Input on AUX2
#endif

// define digital pin 4 for the filament runout sensor. Use the RAMPS 1.4 digital input 4 on the servos connector
#ifndef FIL_RUNOUT_PIN
  #define FIL_RUNOUT_PIN    4
#endif

#ifndef PS_ON_PIN
  #define PS_ON_PIN        12
#endif
*/

//
// M3/M4/M5 - Spindle/Laser Control
//


//
// Průša i3 MK2 Multiplexer Support
//
/*#ifndef E_MUX0_PIN
  #define E_MUX0_PIN 40   // Z_CS_PIN
#endif
#ifndef E_MUX1_PIN
  #define E_MUX1_PIN 42   // E0_CS_PIN
#endif
#ifndef E_MUX2_PIN
  #define E_MUX2_PIN 44   // E1_CS_PIN
#endif
*/
//////////////////////////
// LCDs and Controllers //
//////////////////////////

#if ENABLED(ULTRA_LCD)

  //
  // LCD Display output pins
  //
  #if ENABLED(REPRAPWORLD_GRAPHICAL_LCD)



  #else

    #if ENABLED(CR10_STOCKDISPLAY)



    #else

      #if ENABLED(MKS_12864OLED) || ENABLED(MKS_12864OLED_SSD1306)
 /*       #define LCD_PINS_DC     25   // Set as output on init
        #define LCD_PINS_RS     27   // Pull low for 1s to init
        // DOGM SPI LCD Support
        #define DOGLCD_CS       16
        #define DOGLCD_MOSI     17
        #define DOGLCD_SCK      23
        #define DOGLCD_A0       LCD_PINS_DC
        */
      #else //stm32
	  	#ifdef REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER
	        #define LCD_PINS_RS     28//0xEE//0xC6// 0xDA//0xE6 //T_PEN
	        #define LCD_PINS_ENABLE  29//0xBA//0xEF //D11
	        #define LCD_PINS_D4       27 //0xC8 //D19
        #else
		/*	#define LCD_PINS_RS     5//0xEE //T_PEN
	        #define LCD_PINS_ENABLE 12 //D11
	        #define LCD_PINS_D4     13 //D13
	        #define LCD_PINS_D5     14//0xED //D14
	        #define LCD_PINS_D6     12 //D15
			#define LCD_PINS_D7     14//D12
*/
		#endif

		
       //
		 ///////////////////
 /*  #define SD_DETECT_PIN   31 // 0xC7//49
   #define SD_SPI_SCK	30//0xA5//
   #define SD_SPI_MISO	 30// 0xA6
   #define SD_SPI_MOSI	 31//0xA7
   #define SD_SPI_CS   30//0xA4
//   #define SD_SPI_REMAP  30 
   #define SD_SPI_NUM	1
		/////////////////////////////  
   #define SDSS               SD_SPI_CS//53	 */
/////////


////////
      #endif

     // 

      #if DISABLED(NEWPANEL)
 //        #define BEEPER_PIN      20
		 
      #endif

    #endif

    #if DISABLED(NEWPANEL)
      // Buttons are attached to a shift register
      // Not wired yet
      //#define SHIFT_CLK       38
      //#define SHIFT_LD        42
      //#define SHIFT_OUT       40
      //#define SHIFT_EN        17
    #endif

  #endif

  //
  // LCD Display input pins
  //
  #if ENABLED(NEWPANEL)
   #define BEEPER_PIN		 24// 0xBD//0xEC
   #define BTN_ENC 		21//0xEF//0xED
 
   #define BTN_EN1 		22//0xE9
   #define BTN_EN2 		23//0xE8

  #endif // NEWPANEL

#endif // ULTRA_LCD



#ifndef BOARD_NAME
  #define BOARD_NAME "PANDA,PI"
#endif
//
// Servos
//

//#define SERVO0_PIN       2// 0xBE

//
#define X_MIN_PIN           1//0xE5

#define Y_MIN_PIN          4//0xE3
//#define Y_MAX_PIN          //0xBD//0xE2

//#define Z_MAX_PIN          // 0xB8//0xE0

#if ENABLED(BLTOUCH)
#define Z_MIN_PIN          11//0xE1

#else
#define Z_MIN_PIN            11//0xE1

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
#define X_STEP_PIN         7//0xE3//0xC6
#define X_DIR_PIN          2//0xDD
#define X_ENABLE_PIN       0//0xA8//38

#define Y_STEP_PIN        12// 0xAC
#define Y_DIR_PIN         5// 0xAB
#define Y_ENABLE_PIN      0//0XAF

#define Z_STEP_PIN         14// 0xD6
#define Z_DIR_PIN          13//0xD3
#define Z_ENABLE_PIN       0//0xA3


#define E0_STEP_PIN        10//0xB2
#define E0_DIR_PIN         6//0xBB
#define E0_ENABLE_PIN      0//0xC4

//#define E1_STEP_PIN        12
//#define E1_DIR_PIN         12
//#define E1_ENABLE_PIN      12

/**
 * Default pins for TMC software SPI
 */

#if HAS_DRIVER(TMC2208)

#endif

//
// Temperature Sensors
//
//#define TEMP_0_PIN        11//0xB1// 13   // Analog Input
//#define TEMP_1_PIN        11//0xB0   // Analog Input
//#define TEMP_2_PIN        0xC0//0xB0   // Analog Input
//#define TEMP_BED_PIN      11//0xC5   // Analog Input
//#define TEMP_BOARD_PIN        11//0xB0   // Analog Input

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
//#ifndef RAMPS_D8_PIN
//  #define RAMPS_D8_PIN   0xA2//0xC4  // bed pin
//#endif
//#ifndef RAMPS_D9_PIN
//  #define RAMPS_D9_PIN      0xA1
//#endif
//#ifndef RAMPS_D10_PIN
//  #define RAMPS_D10_PIN  0xA1// GPIOB+GPIO_Pin_0  heater pin
//#endif

#define HEATER_0_PIN     26
#define HEATER_BED_PIN  26//0xD0
#define TEMP_0_PIN     25
#define TEMP_BED_PIN      25
#define TEMP_BOARD_PIN  25

/*

#if EXTRUDERS > 1
#define HEATER_1_PIN     10
#endif
#define FAN_PIN         10
#define FAN1_PIN        14
#define FAN2_PIN        11
#define FAN3_PIN        12
#define FAN4_PIN        17

#define FAN_SOFT_PWM
#if ENABLED(IS_RAMPS_EFB)                      // Hotend, Fan, Bed


#elif ENABLED(IS_RAMPS_EEF)                    // Hotend, Hotend, Fan

  #define HEATER_1_PIN   RAMPS_D9_PIN
  #define FAN_PIN        RAMPS_D8_PIN
#elif ENABLED(IS_RAMPS_EEB)                    // Hotend, Hotend, Bed
  //#define HEATER_1_PIN     RAMPS_D9_PIN
  //#define HEATER_BED_PIN   RAMPS_D8_PIN
#elif ENABLED(IS_RAMPS_EFF)                    // Hotend, Fan, Fan
  #define FAN1_PIN         RAMPS_D8_PIN
#elif DISABLED(IS_RAMPS_SF)                    // Not Spindle, Fan (i.e., "EFBF" or "EFBE")
  #define HEATER_BED_PIN   RAMPS_D8_PIN
  #if HOTENDS == 1
    #define FAN1_PIN       MOSFET_D_PIN
  #else
    #define HEATER_1_PIN   MOSFET_D_PIN
  #endif
#endif

#ifndef FAN_PIN
  #if ENABLED(IS_RAMPS_EFB) || ENABLED(IS_RAMPS_EFF)  // Hotend, Fan, Bed or Hotend, Fan, Fan
    #define FAN_PIN        RAMPS_D9_PIN
  #elif ENABLED(IS_RAMPS_EEF) || ENABLED(IS_RAMPS_SF) // Hotend, Hotend, Fan or Spindle, Fan
    #define FAN_PIN        RAMPS_D8_PIN
  #elif ENABLED(IS_RAMPS_EEB)                         // Hotend, Hotend, Bed
    #define FAN_PIN         4   // IO pin. Buffer needed
  #else                                               // Non-specific are "EFB" (i.e., "EFBF" or "EFBE")
    #define FAN_PIN        RAMPS_D9_PIN
  #endif
#endif

//
// Misc. Functions
//
//
#define LED_PIN            13

#ifndef FILWIDTH_PIN
  #define FILWIDTH_PIN      5   // Analog Input on AUX2
#endif

// define digital pin 4 for the filament runout sensor. Use the RAMPS 1.4 digital input 4 on the servos connector
#ifndef FIL_RUNOUT_PIN
  #define FIL_RUNOUT_PIN    4
#endif

#ifndef PS_ON_PIN
  #define PS_ON_PIN        12
#endif
*/

//
// M3/M4/M5 - Spindle/Laser Control
//


//
// Průša i3 MK2 Multiplexer Support
//
/*#ifndef E_MUX0_PIN
  #define E_MUX0_PIN 40   // Z_CS_PIN
#endif
#ifndef E_MUX1_PIN
  #define E_MUX1_PIN 42   // E0_CS_PIN
#endif
#ifndef E_MUX2_PIN
  #define E_MUX2_PIN 44   // E1_CS_PIN
#endif
*/
//////////////////////////
// LCDs and Controllers //
//////////////////////////

#if ENABLED(ULTRA_LCD)

  //
  // LCD Display output pins
  //
  #if ENABLED(REPRAPWORLD_GRAPHICAL_LCD)



  #else

    #if ENABLED(CR10_STOCKDISPLAY)



    #else

      #if ENABLED(MKS_12864OLED) || ENABLED(MKS_12864OLED_SSD1306)
 /*       #define LCD_PINS_DC     25   // Set as output on init
        #define LCD_PINS_RS     27   // Pull low for 1s to init
        // DOGM SPI LCD Support
        #define DOGLCD_CS       16
        #define DOGLCD_MOSI     17
        #define DOGLCD_SCK      23
        #define DOGLCD_A0       LCD_PINS_DC
        */
      #else //stm32
	  	#ifdef REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER
	        #define LCD_PINS_RS     28//0xEE//0xC6// 0xDA//0xE6 //T_PEN
	        #define LCD_PINS_ENABLE  29//0xBA//0xEF //D11
	        #define LCD_PINS_D4       27 //0xC8 //D19
        #else
		/*	#define LCD_PINS_RS     5//0xEE //T_PEN
	        #define LCD_PINS_ENABLE 12 //D11
	        #define LCD_PINS_D4     13 //D13
	        #define LCD_PINS_D5     14//0xED //D14
	        #define LCD_PINS_D6     12 //D15
			#define LCD_PINS_D7     14//D12
*/
		#endif

		
       //
		 ///////////////////
 /*  #define SD_DETECT_PIN   31 // 0xC7//49
   #define SD_SPI_SCK	30//0xA5//
   #define SD_SPI_MISO	 30// 0xA6
   #define SD_SPI_MOSI	 31//0xA7
   #define SD_SPI_CS   30//0xA4
//   #define SD_SPI_REMAP  30 
   #define SD_SPI_NUM	1
		/////////////////////////////  
   #define SDSS               SD_SPI_CS//53	 */
/////////


////////
      #endif

     // 

      #if DISABLED(NEWPANEL)
 //        #define BEEPER_PIN      20
		 
      #endif

    #endif

    #if DISABLED(NEWPANEL)
      // Buttons are attached to a shift register
      // Not wired yet
      //#define SHIFT_CLK       38
      //#define SHIFT_LD        42
      //#define SHIFT_OUT       40
      //#define SHIFT_EN        17
    #endif

  #endif

  //
  // LCD Display input pins
  //
  #if ENABLED(NEWPANEL)
   #define BEEPER_PIN		 24// 0xBD//0xEC
   #define BTN_ENC 		30//0xEF//0xED
 
   #define BTN_EN1 		22//0xE9
   #define BTN_EN2 		23//0xE8

  #endif // NEWPANEL

#endif // ULTRA_LCD


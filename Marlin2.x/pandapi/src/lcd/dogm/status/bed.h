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
#pragma once

//
// lcd/dogm/status/bed.h - Status Screen Bed bitmaps
//

#if ENABLED(STATUS_ALT_BED_BITMAP)

  #define STATUS_BED_ANIM
  #define STATUS_BED_WIDTH  24
  #ifndef STATUS_BED_X
    #define STATUS_BED_X   (LCD_PIXEL_WIDTH - (STATUS_BED_BYTEWIDTH + STATUS_CHAMBER_BYTEWIDTH + STATUS_FAN_BYTEWIDTH) * 8)
  #endif
  #define STATUS_BED_TEXT_X (STATUS_BED_X + 11)

    const unsigned char status_bed_bmp[] PROGMEM = {
      0B11111111,0B11111111,0B11000000,
      0B01000000,0B00000000,0B00100000,
      0B00100000,0B00000000,0B00010000,
      0B00010000,0B00000000,0B00001000,
      0B00001000,0B00000000,0B00000100,
      0B00000100,0B00000000,0B00000010,
      0B00000011,0B11111111,0B11111111
    };

    const unsigned char status_bed_on_bmp[] PROGMEM = {
      0B00000010,0B00100010,0B00000000,
      0B00000100,0B01000100,0B00000000,
      0B00000100,0B01000100,0B00000000,
      0B00000010,0B00100010,0B00000000,
      0B00000001,0B00010001,0B00000000,
      0B11111111,0B11111111,0B11000000,
      0B01000000,0B10001000,0B10100000,
      0B00100001,0B00010001,0B00010000,
      0B00010010,0B00100010,0B00001000,
      0B00001000,0B00000000,0B00000100,
      0B00000100,0B00000000,0B00000010,
      0B00000011,0B11111111,0B11111111
    };

#else

  #define STATUS_BED_WIDTH  21
  #ifndef STATUS_BED_X
    #define STATUS_BED_X   (LCD_PIXEL_WIDTH - (STATUS_BED_BYTEWIDTH + STATUS_CHAMBER_BYTEWIDTH + STATUS_FAN_BYTEWIDTH) * 8)
  #endif

  #ifdef STATUS_BED_ANIM

      const unsigned char status_bed_bmp[] PROGMEM = {
        0B00011111,0B11111111,0B11111000,
        0B00011111,0B11111111,0B11111000
      };

      const unsigned char status_bed_on_bmp[] PROGMEM = {
        0B00000100,0B00010000,0B01000000,
        0B00000010,0B00001000,0B00100000,
        0B00000010,0B00001000,0B00100000,
        0B00000100,0B00010000,0B01000000,
        0B00001000,0B00100000,0B10000000,
        0B00010000,0B01000001,0B00000000,
        0B00010000,0B01000001,0B00000000,
        0B00001000,0B00100000,0B10000000,
        0B00000100,0B00010000,0B01000000,
        0B00000000,0B00000000,0B00000000,
        0B00011111,0B11111111,0B11111000,
        0B00011111,0B11111111,0B11111000
      };

  #else

    const unsigned char status_bed_bmp[] PROGMEM = {
        0B00000100,0B00010000,0B01000000,
        0B00000010,0B00001000,0B00100000,
        0B00000010,0B00001000,0B00100000,
        0B00000100,0B00010000,0B01000000,
        0B00001000,0B00100000,0B10000000,
        0B00010000,0B01000001,0B00000000,
        0B00010000,0B01000001,0B00000000,
        0B00001000,0B00100000,0B10000000,
        0B00000100,0B00010000,0B01000000,
        0B00000000,0B00000000,0B00000000,
        0B00011111,0B11111111,0B11111000,
        0B00011111,0B11111111,0B11111000
    };

  #endif

#endif

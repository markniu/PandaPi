/*

  U8glib.h

  C++ Interface

  Universal 8bit Graphics Library

  Copyright (c) 2011, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list
    of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice, this
    list of conditions and the following disclaimer in the documentation and/or other
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#pragma once
#define U8G_HAL_LINKS // PANDAPI

#ifdef U8G_HAL_LINKS
  #include "../U8glibPrint.h"
  #define U8GLIB_PRINT_CLASS U8glibPrint
  #include "u8g.h"
#else
  #include <Print.h>
#include "u8g.h"
  #define U8GLIB_PRINT_CLASS Print
#endif

//#include "clib/u8g.h"

class U8GLIB : public U8GLIB_PRINT_CLASS {
  private:
    u8g_t u8g;
    u8g_uint_t tx, ty;          // current position for the Print base class procedures
    uint8_t is_begin;

    void prepare() { tx = 0; ty = 0; is_begin = 0; }
    void cbegin() { if ( is_begin == 0 ) { is_begin = 1; u8g_Begin(&u8g); } }
    uint8_t initSPI(u8g_dev_t *dev, uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE);
    uint8_t initHWSPI(u8g_dev_t *dev, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE);
    uint8_t initI2C(u8g_dev_t *dev, uint8_t options);
  protected:
    uint8_t init8BitFixedPort(u8g_dev_t *dev, uint8_t en, uint8_t cs, uint8_t di, uint8_t rw, uint8_t reset);
  private:
    uint8_t init8Bit(u8g_dev_t *dev, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t en, uint8_t cs1, uint8_t cs2, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE);
    uint8_t initRW8Bit(u8g_dev_t *dev, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t cs, uint8_t a0, uint8_t wr, uint8_t rd, uint8_t reset);
  public:

    /* constructor */
    U8GLIB() { }
    U8GLIB(u8g_dev_t *dev)                                                                   { init(dev); }
    U8GLIB(u8g_dev_t *dev, u8g_com_fnptr com_fn)                                             { init(dev, com_fn); }
    U8GLIB(u8g_dev_t *dev, uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset) { init(dev, sck, mosi, cs, a0, reset); }
    U8GLIB(u8g_dev_t *dev, uint8_t cs, uint8_t a0, uint8_t reset)                            { init(dev, cs, a0, reset); }
    U8GLIB(u8g_dev_t *dev, uint8_t options)                                                  { init(dev, options); }
    U8GLIB(u8g_dev_t *dev, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t en, uint8_t cs1, uint8_t cs2, uint8_t di, uint8_t rw, uint8_t reset)
      { init(dev, d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, cs2, di, rw, reset); }
    U8GLIB(u8g_dev_t *dev, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t cs, uint8_t a0, uint8_t wr, uint8_t rd, uint8_t reset)
      { init(dev, d0, d1, d2, d3, d4, d5, d6, d7, cs, a0, wr, rd, reset); }

    /* initializer */
    void init(u8g_dev_t *dev)                                                                   { prepare(); (void)u8g_Init(&u8g, dev); }
    void init(u8g_dev_t *dev, u8g_com_fnptr com_fn)                                             { prepare(); (void)u8g_InitComFn(&u8g, dev, com_fn); }
    void init(u8g_dev_t *dev, uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset) { (void)initSPI(dev, sck, mosi, cs, a0, reset); }
    void init(u8g_dev_t *dev, uint8_t cs, uint8_t a0, uint8_t reset)                            { (void)initHWSPI(dev, cs, a0, reset); }
    void init(u8g_dev_t *dev, uint8_t options)                                                  { (void)initI2C(dev, options); }
    void init(u8g_dev_t *dev, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t en, uint8_t cs1, uint8_t cs2, uint8_t di, uint8_t rw, uint8_t reset)
      { (void)init8Bit(dev, d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, cs2, di, rw, reset); }
    void init(u8g_dev_t *dev, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t cs, uint8_t a0, uint8_t wr, uint8_t rd, uint8_t reset)
      { (void)initRW8Bit(dev, d0, d1, d2, d3, d4, d5, d6, d7, cs, a0, wr, rd, reset); }

    uint8_t begin() { is_begin = 1; return u8g_Begin(&u8g); }

    void setPrintPos(u8g_uint_t x, u8g_uint_t y) { tx = x; ty = y; }
    u8g_t *getU8g() { return &u8g; }
    u8g_uint_t getPrintCol() { return tx; }
    u8g_uint_t getPrintRow() { return ty; }

    /* implementation of the write interface to the print class */
    #if defined(ARDUINO) && ARDUINO < 100
      void write(uint8_t c) { tx += u8g_DrawGlyph(&u8g, tx, ty, c); }
    #else
      size_t write(uint8_t c) { tx += u8g_DrawGlyph(&u8g, tx, ty, c); return 1;}
    #endif

     /* screen rotation */
    void undoRotation() { u8g_UndoRotation(&u8g); }
    void setRot90() { u8g_SetRot90(&u8g); }
    void setRot180() { u8g_SetRot180(&u8g); }
    void setRot270() { u8g_SetRot270(&u8g); }

     /* screen scaling */
    void undoScale() { u8g_UndoScale(&u8g); }
    void setScale2x2() { u8g_SetScale2x2(&u8g); }

     /* picture loop */
    void firstPage() { cbegin(); u8g_FirstPage(&u8g); }
    uint8_t nextPage() { return u8g_NextPage(&u8g); }

    /* system commands */
    uint8_t setContrast(uint8_t contrast) { cbegin(); return u8g_SetContrast(&u8g, contrast); }
    void sleepOn() { u8g_SleepOn(&u8g); }
    void sleepOff() { u8g_SleepOff(&u8g); }

    /* graphic primitives */
    void setColorEntry(uint8_t color_index, uint8_t r, uint8_t g, uint8_t b) { u8g_SetColorEntry(&u8g, color_index, r, g, b); }
    void setHiColor(uint16_t  rgb) { u8g_SetHiColor(&u8g, rgb); }
    void setHiColorByRGB(uint8_t r, uint8_t g, uint8_t b) { u8g_SetHiColorByRGB(&u8g, r, g, b); }
    void setRGB(uint8_t r, uint8_t g, uint8_t b) { u8g_SetRGB(&u8g, r, g, b); }

    void setColorIndex(uint8_t color_index) { u8g_SetColorIndex(&u8g, color_index); }
    uint8_t getColorIndex() { return u8g_GetColorIndex(&u8g); }

    void setDefaultForegroundColor() { u8g_SetDefaultForegroundColor(&u8g);  }
    void setDefaultBackgroundColor() { u8g_SetDefaultBackgroundColor(&u8g);  }
    void setDefaultMidColor() { u8g_SetDefaultMidColor(&u8g);  }

    u8g_uint_t getWidth() { return u8g_GetWidth(&u8g); }
    u8g_uint_t getHeight() { return u8g_GetHeight(&u8g); }
    uint8_t getMode() { return u8g_GetMode(&u8g); }

    void drawPixel(u8g_uint_t x, u8g_uint_t y) { return u8g_DrawPixel(&u8g, x, y); }
    void drawHLine(u8g_uint_t x, u8g_uint_t y, u8g_uint_t w) { u8g_DrawHLine(&u8g, x, y, w); }
    void drawVLine(u8g_uint_t x, u8g_uint_t y, u8g_uint_t h) { u8g_DrawVLine(&u8g, x, y, h); }
    void drawLine(u8g_uint_t x1, u8g_uint_t y1, u8g_uint_t x2, u8g_uint_t y2) { u8g_DrawLine(&u8g, x1, y1, x2, y2); }

    void drawFrame(u8g_uint_t x, u8g_uint_t y, u8g_uint_t w, u8g_uint_t h) { u8g_DrawFrame(&u8g, x, y, w, h); }
    void drawRFrame(u8g_uint_t x, u8g_uint_t y, u8g_uint_t w, u8g_uint_t h, u8g_uint_t r) { u8g_DrawRFrame(&u8g, x, y, w, h,r); }
    void drawBox(u8g_uint_t x, u8g_uint_t y, u8g_uint_t w, u8g_uint_t h) { u8g_DrawBox(&u8g, x, y, w, h); }
    void drawRBox(u8g_uint_t x, u8g_uint_t y, u8g_uint_t w, u8g_uint_t h, u8g_uint_t r) { u8g_DrawRBox(&u8g, x, y, w, h,r); }

    void drawCircle(u8g_uint_t x0, u8g_uint_t y0, u8g_uint_t rad, uint8_t opt = U8G_DRAW_ALL) { u8g_DrawCircle(&u8g, x0, y0, rad, opt); }
    void drawDisc(u8g_uint_t x0, u8g_uint_t y0, u8g_uint_t rad, uint8_t opt = U8G_DRAW_ALL) { u8g_DrawDisc(&u8g, x0, y0, rad, opt); }

    void drawEllipse(u8g_uint_t x0, u8g_uint_t y0, u8g_uint_t rx, u8g_uint_t ry, uint8_t opt = U8G_DRAW_ALL) { u8g_DrawEllipse(&u8g, x0, y0, rx, ry, opt); }
    void drawFilledEllipse(u8g_uint_t x0, u8g_uint_t y0, u8g_uint_t rx, u8g_uint_t ry, uint8_t opt = U8G_DRAW_ALL) { u8g_DrawFilledEllipse(&u8g, x0, y0, rx, ry, opt); }

    void drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
      { u8g_DrawTriangle(&u8g, x0, y0, x1, y1, x2, y2); }


    /* bitmap handling */
    void drawBitmap(u8g_uint_t x, u8g_uint_t y, u8g_uint_t cnt, u8g_uint_t h, const uint8_t *bitmap)
      { u8g_DrawBitmap(&u8g, x, y, cnt, h, bitmap); }
    void drawBitmapP(u8g_uint_t x, u8g_uint_t y, u8g_uint_t cnt, u8g_uint_t h, const u8g_pgm_uint8_t *bitmap)
      { u8g_DrawBitmapP(&u8g, x, y, cnt, h, bitmap); }

    void drawXBM(u8g_uint_t x, u8g_uint_t y, u8g_uint_t w, u8g_uint_t h, const uint8_t *bitmap)
      { u8g_DrawXBM(&u8g, x, y, w, h, bitmap); }
    void drawXBMP(u8g_uint_t x, u8g_uint_t y, u8g_uint_t w, u8g_uint_t h, const u8g_pgm_uint8_t *bitmap)
      { u8g_DrawXBMP(&u8g, x, y, w, h, bitmap); }


    /* font handling */
    void setFont(const u8g_fntpgm_uint8_t *font) {u8g_SetFont(&u8g, font); }
    int8_t getFontAscent() { return u8g_GetFontAscent(&u8g); }
    int8_t getFontDescent() { return u8g_GetFontDescent(&u8g); }
    int8_t getFontLineSpacing() { return u8g_GetFontLineSpacing(&u8g); }

    u8g_uint_t drawStr(u8g_uint_t x, u8g_uint_t y, const char *s) { return u8g_DrawStr(&u8g, x, y, s); }
    u8g_uint_t drawStr90(u8g_uint_t x, u8g_uint_t y, const char *s) { return u8g_DrawStr90(&u8g, x, y, s); }
    u8g_uint_t drawStr180(u8g_uint_t x, u8g_uint_t y, const char *s) { return u8g_DrawStr180(&u8g, x, y, s); }
    u8g_uint_t drawStr270(u8g_uint_t x, u8g_uint_t y, const char *s) { return u8g_DrawStr270(&u8g, x, y, s); }
    u8g_uint_t drawStrP(u8g_uint_t x, u8g_uint_t y, const u8g_pgm_uint8_t *s) { return u8g_DrawStrP(&u8g, x, y, s); }
    u8g_uint_t drawStr90P(u8g_uint_t x, u8g_uint_t y, const u8g_pgm_uint8_t *s) { return u8g_DrawStr90P(&u8g, x, y, s); }
    u8g_uint_t drawStr180P(u8g_uint_t x, u8g_uint_t y, const u8g_pgm_uint8_t *s) { return u8g_DrawStr180P(&u8g, x, y, s); }
    u8g_uint_t drawStr270P(u8g_uint_t x, u8g_uint_t y, const u8g_pgm_uint8_t *s) { return u8g_DrawStr270P(&u8g, x, y, s); }

    void setFontPosBaseline() { u8g_SetFontPosBaseline(&u8g); }
    void setFontPosBottom() { u8g_SetFontPosBottom(&u8g); }
    void setFontPosCenter() { u8g_SetFontPosCenter(&u8g); }
    void setFontPosTop() { u8g_SetFontPosTop(&u8g); }

    void setFontRefHeightText() { u8g_SetFontRefHeightText(&u8g); }
    void setFontRefHeightExtendedText() { u8g_SetFontRefHeightExtendedText(&u8g); }
    void setFontRefHeightAll() { u8g_SetFontRefHeightAll(&u8g); }
    void setFontLineSpacingFactor(uint8_t factor) { u8g_SetFontLineSpacingFactor(&u8g, factor); }


    u8g_uint_t getStrPixelWidth(const char *s) { return u8g_GetStrPixelWidth(&u8g, s); }
    u8g_uint_t getStrPixelWidthP(u8g_pgm_uint8_t *s) { return u8g_GetStrPixelWidthP(&u8g, s); }
    u8g_uint_t getStrWidth(const char *s) { return u8g_GetStrWidth(&u8g, s); }
    u8g_uint_t getStrWidthP(u8g_pgm_uint8_t *s) { return u8g_GetStrWidthP(&u8g, s); }
    int8_t getGlyphDeltaX(uint8_t requested_encoding) { return u8g_GetGlyphDeltaX(&u8g, requested_encoding); }

    void setHardwareBackup(u8g_state_cb backup_cb) { u8g_SetHardwareBackup(&u8g, backup_cb); }

#if defined(ARDUINO) && ARDUINO >= 100 && !defined(U8G_HAL_LINKS)
      //  generates false compiler errors when U8G_HAL_LINKS is enabled
    // support for the F() macro

    u8g_uint_t drawStr(u8g_uint_t x, u8g_uint_t y, const __FlashStringHelper *s) { return u8g_DrawStrP(&u8g, x, y, (u8g_pgm_uint8_t *)s); }
    u8g_uint_t drawStr90(u8g_uint_t x, u8g_uint_t y, const __FlashStringHelper *s) { return u8g_DrawStr90P(&u8g, x, y, (u8g_pgm_uint8_t *)s); }
    u8g_uint_t drawStr180(u8g_uint_t x, u8g_uint_t y, const __FlashStringHelper *s) { return u8g_DrawStr180P(&u8g, x, y, (u8g_pgm_uint8_t *)s); }
    u8g_uint_t drawStr270(u8g_uint_t x, u8g_uint_t y, const __FlashStringHelper *s) { return u8g_DrawStr270P(&u8g, x, y, (u8g_pgm_uint8_t *)s); }

    u8g_uint_t getStrPixelWidth(const __FlashStringHelper *s) { return u8g_GetStrPixelWidthP(&u8g, (u8g_pgm_uint8_t *)s); }
    u8g_uint_t getStrWidth(const __FlashStringHelper *s) { return u8g_GetStrWidthP(&u8g, (u8g_pgm_uint8_t *)s); }
#endif
    /* cursor handling */
    void setCursorFont(const u8g_pgm_uint8_t *cursor_font) { u8g_SetCursorFont(&u8g, cursor_font); }
    void setCursorStyle(uint8_t encoding) { u8g_SetCursorStyle(&u8g, encoding); }
    void setCursorPos(u8g_uint_t cursor_x, u8g_uint_t cursor_y) { u8g_SetCursorPos(&u8g, cursor_x, cursor_y); }
    void setCursorColor(uint8_t fg, uint8_t bg) { u8g_SetCursorColor(&u8g, fg, bg); }
    void enableCursor() { u8g_EnableCursor(&u8g); }
    void disableCursor() { u8g_DisableCursor(&u8g); }
    void drawCursor()  { u8g_DrawCursor(&u8g); }

    /* virtual screen */

    void setVirtualScreenDimension(u8g_uint_t width, u8g_uint_t height) { u8g_SetVirtualScreenDimension(&u8g, width, height); }
    uint8_t addToVirtualScreen(u8g_uint_t x, u8g_uint_t y, U8GLIB &child_u8g) { return u8g_AddToVirtualScreen(&u8g, x, y, &child_u8g.u8g); }

};

/* subclasses for specific displays */

class U8GLIB_DOGS102 : public U8GLIB {
public:
  U8GLIB_DOGS102() : U8GLIB() { }
  U8GLIB_DOGS102(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_DOGS102(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1701_dogs102_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1701_dogs102_hw_spi, cs, a0, reset); }
};

class U8GLIB_DOGS102_2X : public U8GLIB {
public:
  U8GLIB_DOGS102_2X() : U8GLIB() { }
  U8GLIB_DOGS102_2X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_DOGS102_2X(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1701_dogs102_2x_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1701_dogs102_2x_hw_spi, cs, a0, reset); }
};

class U8GLIB_MINI12864 : public U8GLIB {
public:
  U8GLIB_MINI12864() : U8GLIB() { }
  U8GLIB_MINI12864(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_MINI12864(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1701_mini12864_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1701_mini12864_hw_spi, cs, a0, reset); }
};

class U8GLIB_MINI12864_2X : public U8GLIB {
public:
  U8GLIB_MINI12864_2X() : U8GLIB() { }
  U8GLIB_MINI12864_2X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_MINI12864_2X(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1701_mini12864_2x_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1701_mini12864_2x_hw_spi, cs, a0, reset); }
};

class U8GLIB_DOGM132 : public U8GLIB {
public:
  U8GLIB_DOGM132() : U8GLIB() { }
  U8GLIB_DOGM132(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_DOGM132(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_dogm132_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_dogm132_hw_spi, cs, a0, reset); }
};

class U8GLIB_NHD_C12832 : public U8GLIB {
public:
  U8GLIB_NHD_C12832() : U8GLIB() { }
  U8GLIB_NHD_C12832(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_NHD_C12832(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_NHD_C12832(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                    uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, di, rw, reset);
  }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_nhd_c12832_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_nhd_c12832_hw_spi, cs, a0, reset); }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_st7565_nhd_c12832_parallel, d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, U8G_PIN_NONE, di, rw, reset);
  }
};

class U8GLIB_NHD_C12832_USART : public U8GLIB {
public:
  U8GLIB_NHD_C12832_USART() : U8GLIB() { }
  U8GLIB_NHD_C12832_USART(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_nhd_c12832_hw_usart_spi, cs, a0, reset); }
};

class U8GLIB_DOGM128 : public U8GLIB {
public:
  U8GLIB_DOGM128() : U8GLIB() { }
  U8GLIB_DOGM128(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_DOGM128(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_DOGM128(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                 uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, di, rw, reset);
  }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_dogm128_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_dogm128_hw_spi, cs, a0, reset); }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_st7565_dogm128_parallel, d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, U8G_PIN_NONE, di, rw, reset);
  }
};

class U8GLIB_DOGM128_2X : public U8GLIB {
public:
  U8GLIB_DOGM128_2X() : U8GLIB() { }
  U8GLIB_DOGM128_2X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_DOGM128_2X(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_DOGM128_2X(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                    uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, di, rw, reset);
  }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_dogm128_2x_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_dogm128_2x_hw_spi, cs, a0, reset); }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_st7565_dogm128_2x_parallel, d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, U8G_PIN_NONE, di, rw, reset);
  }
};

class U8GLIB_LM6059 : public U8GLIB {
public:
  U8GLIB_LM6059() : U8GLIB() { }
  U8GLIB_LM6059(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_LM6059(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_lm6059_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_lm6059_hw_spi, cs, a0, reset); }
};

class U8GLIB_LM6059_2X : public U8GLIB {
public:
  U8GLIB_LM6059_2X() : U8GLIB() { }
  U8GLIB_LM6059_2X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_LM6059_2X(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_lm6059_2x_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_lm6059_2x_hw_spi, cs, a0, reset); }
};

class U8GLIB_LM6063 : public U8GLIB {
public:
  U8GLIB_LM6063() : U8GLIB() { }
  U8GLIB_LM6063(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_LM6063(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_lm6063_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_lm6063_hw_spi, cs, a0, reset); }
};

class U8GLIB_LM6063_2X : public U8GLIB {
public:
  U8GLIB_LM6063_2X() : U8GLIB() { }
  U8GLIB_LM6063_2X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_LM6063_2X(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_lm6063_2x_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_lm6063_2x_hw_spi, cs, a0, reset); }
};

class U8GLIB_64128N : public U8GLIB {
public:
  U8GLIB_64128N() : U8GLIB() { }
  U8GLIB_64128N(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_64128N(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_64128N(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, di, rw, reset);
  }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_64128n_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_64128n_hw_spi, cs, a0, reset); }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_st7565_64128n_parallel, d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, U8G_PIN_NONE, di, rw, reset);
  }
};

class U8GLIB_64128N_2X : public U8GLIB {
public:
  U8GLIB_64128N_2X() : U8GLIB() { }
  U8GLIB_64128N_2X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_64128N_2X(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_64128N_2X(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                   uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, di, rw, reset);
  }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_64128n_2x_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_64128n_2x_hw_spi, cs, a0, reset); }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_st7565_64128n_2x_parallel, d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, U8G_PIN_NONE, di, rw, reset);
  }
};

class U8GLIB_NHD_C12864 : public U8GLIB {
public:
  U8GLIB_NHD_C12864() : U8GLIB() { }
  U8GLIB_NHD_C12864(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_NHD_C12864(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_nhd_c12864_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_nhd_c12864_hw_spi, cs, a0, reset); }
};

class U8GLIB_NHD_C12864_2X : public U8GLIB {
public:
  U8GLIB_NHD_C12864_2X() : U8GLIB() { }
  U8GLIB_NHD_C12864_2X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_NHD_C12864_2X(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_nhd_c12864_2x_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7565_nhd_c12864_2x_hw_spi, cs, a0, reset); }
};

class U8GLIB_UC1601_C128032 : public U8GLIB {
public:
  U8GLIB_UC1601_C128032() : U8GLIB() { }
  U8GLIB_UC1601_C128032(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_UC1601_C128032(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1601_c128032_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1601_c128032_hw_spi, cs, a0, reset); }
};

class U8GLIB_UC1601_C128032_2X : public U8GLIB {
public:
  U8GLIB_UC1601_C128032_2X() : U8GLIB() { }
  U8GLIB_UC1601_C128032_2X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_UC1601_C128032_2X(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1601_c128032_2x_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1601_c128032_2x_hw_spi, cs, a0, reset); }
};

class U8GLIB_UC1608_240X64 : public U8GLIB {
public:
  U8GLIB_UC1608_240X64() : U8GLIB() { }
  U8GLIB_UC1608_240X64(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_UC1608_240X64(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1608_240x64_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1608_240x64_hw_spi, cs, a0, reset); }
};

class U8GLIB_UC1608_240X64_2X : public U8GLIB {
public:
  U8GLIB_UC1608_240X64_2X() : U8GLIB() { }
  U8GLIB_UC1608_240X64_2X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_UC1608_240X64_2X(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1608_240x64_2x_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1608_240x64_2x_hw_spi, cs, a0, reset); }
};

class U8GLIB_UC1608_240X128 : public U8GLIB {
public:
  U8GLIB_UC1608_240X128() : U8GLIB() { }
  U8GLIB_UC1608_240X128(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_UC1608_240X128(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1608_240x128_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1608_240x128_hw_spi, cs, a0, reset); }
};

class U8GLIB_UC1608_240X128_2X : public U8GLIB {
public:
  U8GLIB_UC1608_240X128_2X() : U8GLIB() { }
  U8GLIB_UC1608_240X128_2X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_UC1608_240X128_2X(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1608_240x128_2x_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1608_240x128_2x_hw_spi, cs, a0, reset); }
};


class U8GLIB_UC1611_DOGM240 : public U8GLIB {
public:
  U8GLIB_UC1611_DOGM240() : U8GLIB() { }
  U8GLIB_UC1611_DOGM240(uint8_t options) { init(options); }
  U8GLIB_UC1611_DOGM240(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_UC1611_DOGM240(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_UC1611_DOGM240(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                        uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, di, rw, reset);  // cs2 = U8G_PIN_NONE
  }
  void init(uint8_t options = U8G_I2C_OPT_NONE) { U8GLIB::init(&u8g_dev_uc1611_dogm240_i2c, options); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1611_dogm240_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1611_dogm240_hw_spi, cs, a0, reset); }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_uc1611_dogm240_8bit, d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, U8G_PIN_NONE, di, rw, reset); // cs2 = U8G_PIN_NONE
  }
};

class U8GLIB_UC1611_DOGXL240 : public U8GLIB {
public:
  U8GLIB_UC1611_DOGXL240() : U8GLIB() { }
  U8GLIB_UC1611_DOGXL240(uint8_t options) { U8GLIB::init(&u8g_dev_uc1611_dogxl240_i2c, options); }
  U8GLIB_UC1611_DOGXL240(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_UC1611_DOGXL240(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_UC1611_DOGXL240(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, di, rw, reset);  // cs2 = U8G_PIN_NONE
  }
  void init(uint8_t options = U8G_I2C_OPT_NONE) { U8GLIB::init(&u8g_dev_uc1611_dogxl240_i2c, options); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1611_dogxl240_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1611_dogxl240_hw_spi, cs, a0, reset); }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_uc1611_dogxl240_8bit, d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, U8G_PIN_NONE, di, rw, reset);  // cs2 = U8G_PIN_NONE
  }
};

class U8GLIB_ST7920_128X64 : public U8GLIB {
public:
  U8GLIB_ST7920_128X64() : U8GLIB() { }
  U8GLIB_ST7920_128X64(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_ST7920_128X64(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_ST7920_128X64(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                       uint8_t en, uint8_t cs1, uint8_t cs2, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, cs2, di, rw, reset);
  }
  //U8GLIB_ST7920_128X64(uint8_t cs)
  //  : U8GLIB(&u8g_dev_st7920_128x64_sw_spi, cs, U8G_PIN_NONE, U8G_PIN_NONE)
  //  { }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7920_128x64_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7920_128x64_hw_spi, cs, a0, reset); }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t cs1, uint8_t cs2, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_st7920_128x64_8bit, d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, cs2, di, rw, reset);
  }
};

class U8GLIB_ST7920_128X64_1X : public U8GLIB {
public:
  U8GLIB_ST7920_128X64_1X() : U8GLIB() { }
  U8GLIB_ST7920_128X64_1X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, reset); }  // a0 = U8G_PIN_NONE
  U8GLIB_ST7920_128X64_1X(uint8_t cs, uint8_t reset = U8G_PIN_NONE) { init(cs, reset); }  // a0 = U8G_PIN_NONE
  U8GLIB_ST7920_128X64_1X(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, di, rw, reset); // cs1 = cs2 = U8G_PIN_NONE
  }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7920_128x64_sw_spi, sck, mosi, cs, U8G_PIN_NONE, reset); } // a0 = U8G_PIN_NONE
  void init(uint8_t cs, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7920_128x64_hw_spi, cs, U8G_PIN_NONE, reset); }   // a0 = U8G_PIN_NONE
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_st7920_128x64_8bit, d0, d1, d2, d3, d4, d5, d6, d7, en, U8G_PIN_NONE, U8G_PIN_NONE, di, rw, reset); // cs1 = cs2 = U8G_PIN_NONE
  }
};

class U8GLIB_ST7920_128X64_CUSTOM_1X : public U8GLIB {
public:
  U8GLIB_ST7920_128X64_CUSTOM_1X() : U8GLIB() { }
  U8GLIB_ST7920_128X64_CUSTOM_1X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, reset); } // a0 = U8G_PIN_NONE
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7920_128x64_custom, sck, mosi, cs, U8G_PIN_NONE, reset); } // a0 = U8G_PIN_NONE
};

class U8GLIB_ST7920_128X64_4X : public U8GLIB {
public:
  U8GLIB_ST7920_128X64_4X() : U8GLIB() { }
  U8GLIB_ST7920_128X64_4X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, reset); } // a0 = U8G_PIN_NONE
  U8GLIB_ST7920_128X64_4X(uint8_t cs, uint8_t reset = U8G_PIN_NONE) { init(cs, reset); } // a0 = U8G_PIN_NONE
  U8GLIB_ST7920_128X64_4X(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                          uint8_t en, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, di, rw, reset); // cs1 = cs2 = U8G_PIN_NONE
  }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7920_128x64_4x_sw_spi, sck, mosi, cs, U8G_PIN_NONE, reset); } // a0 = U8G_PIN_NONE
  void init(uint8_t cs, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7920_128x64_4x_hw_spi, cs, U8G_PIN_NONE, reset); } // a0 = U8G_PIN_NONE
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_st7920_128x64_4x_8bit, d0, d1, d2, d3, d4, d5, d6, d7, en, U8G_PIN_NONE, U8G_PIN_NONE, di, rw, reset); // cs1 = cs2 = U8G_PIN_NONE
  }
};

class U8GLIB_ST7920_128X64_CUSTOM_4X : public U8GLIB {
public:
  U8GLIB_ST7920_128X64_CUSTOM_4X() : U8GLIB() { }
  U8GLIB_ST7920_128X64_CUSTOM_4X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, reset); } // a0 = U8G_PIN_NONE
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_st7920_128x64_4x_custom, sck, mosi, cs, U8G_PIN_NONE, reset); // a0 = U8G_PIN_NONE
  }
};


class U8GLIB_ST7920_192X32 : public U8GLIB { // OBSOLETE, use U8GLIB_ST7920_192X32_1X instead
public:
  U8GLIB_ST7920_192X32() : U8GLIB() { }
  U8GLIB_ST7920_192X32(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_ST7920_192X32(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_ST7920_192X32(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                       uint8_t en, uint8_t cs1, uint8_t cs2, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, cs2, di, rw, reset);
  }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7920_192x32_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7920_192x32_hw_spi, cs, a0, reset); }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t cs1, uint8_t cs2, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_st7920_192x32_8bit, d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, cs2, di, rw, reset);
  }
};

class U8GLIB_ST7920_192X32_1X : public U8GLIB {
public:
  U8GLIB_ST7920_192X32_1X() : U8GLIB() { }
  U8GLIB_ST7920_192X32_1X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, reset); } // a0 = U8G_PIN_NONE
  U8GLIB_ST7920_192X32_1X(uint8_t cs, uint8_t reset = U8G_PIN_NONE) { init(cs, reset); } // a0 = U8G_PIN_NONE
  U8GLIB_ST7920_192X32_1X(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, di, rw, reset); // cs1 = cs2 = U8G_PIN_NONE
  }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7920_192x32_sw_spi, sck, mosi, cs, U8G_PIN_NONE, reset); } // a0 = U8G_PIN_NONE
  void init(uint8_t cs, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7920_192x32_hw_spi, cs, U8G_PIN_NONE, reset); } // a0 = U8G_PIN_NONE
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
      U8GLIB::init(&u8g_dev_st7920_192x32_8bit, d0, d1, d2, d3, d4, d5, d6, d7, en, U8G_PIN_NONE, U8G_PIN_NONE, di, rw, reset); // cs1 = cs2 = U8G_PIN_NONE
  }
};

class U8GLIB_ST7920_192X32_4X : public U8GLIB {
public:
  U8GLIB_ST7920_192X32_4X() : U8GLIB() { }
  U8GLIB_ST7920_192X32_4X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, reset); } // a0 = U8G_PIN_NONE
  U8GLIB_ST7920_192X32_4X(uint8_t cs, uint8_t reset = U8G_PIN_NONE) { init(cs, reset); } // a0 = U8G_PIN_NONE
  U8GLIB_ST7920_192X32_4X(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, di, rw, reset); // cs1 = cs2 = U8G_PIN_NONE
  }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7920_192x32_4x_sw_spi, sck, mosi, cs, U8G_PIN_NONE, reset); } // a0 = U8G_PIN_NONE
  void init(uint8_t cs, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7920_192x32_4x_hw_spi, cs, U8G_PIN_NONE, reset); } // a0 = U8G_PIN_NONE
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_st7920_192x32_4x_8bit, d0, d1, d2, d3, d4, d5, d6, d7, en, U8G_PIN_NONE, U8G_PIN_NONE, di, rw, reset); // cs1 = cs2 = U8G_PIN_NONE
  }
};


class U8GLIB_ST7920_202X32 : public U8GLIB {
public:
  U8GLIB_ST7920_202X32() : U8GLIB() { }
  U8GLIB_ST7920_202X32(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_ST7920_202X32(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_ST7920_202X32(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t cs1, uint8_t cs2, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) { init(d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, cs2, di, rw, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7920_202x32_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7920_202x32_hw_spi, cs, a0, reset); }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t cs1, uint8_t cs2, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_st7920_202x32_8bit, d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, cs2, di, rw, reset);
  }
};

class U8GLIB_ST7920_202X32_1X : public U8GLIB {
public:
  U8GLIB_ST7920_202X32_1X() : U8GLIB() { }
  U8GLIB_ST7920_202X32_1X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, reset); } // a0 = U8G_PIN_NONE
  U8GLIB_ST7920_202X32_1X(uint8_t cs, uint8_t reset = U8G_PIN_NONE) { init(cs, reset); } // a0 = U8G_PIN_NONE
  U8GLIB_ST7920_202X32_1X(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, di, rw, reset); // cs1 = cs2 = U8G_PIN_NONE
  }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7920_202x32_sw_spi, sck, mosi, cs, U8G_PIN_NONE, reset); } // a0 = U8G_PIN_NONE
  void init(uint8_t cs, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7920_202x32_hw_spi, cs, U8G_PIN_NONE, reset); } // a0 = U8G_PIN_NONE
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_st7920_202x32_8bit, d0, d1, d2, d3, d4, d5, d6, d7, en, U8G_PIN_NONE, U8G_PIN_NONE, di, rw, reset); // cs1 = cs2 = U8G_PIN_NONE
  }
};

class U8GLIB_ST7920_202X32_4X : public U8GLIB {
public:
  U8GLIB_ST7920_202X32_4X() : U8GLIB() { }
  U8GLIB_ST7920_202X32_4X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, reset); } // a0 = U8G_PIN_NONE
  U8GLIB_ST7920_202X32_4X(uint8_t cs, uint8_t reset = U8G_PIN_NONE) { init(cs, reset); } // a0 = U8G_PIN_NONE
  U8GLIB_ST7920_202X32_4X(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                          uint8_t en, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, di, rw, reset); // cs1 = cs2 = U8G_PIN_NONE
  }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7920_202x32_4x_sw_spi, sck, mosi, cs, U8G_PIN_NONE, reset); } // a0 = U8G_PIN_NONE
  void init(uint8_t cs, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7920_202x32_4x_hw_spi, cs, U8G_PIN_NONE, reset); } // a0 = U8G_PIN_NONE
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_st7920_202x32_4x_8bit, d0, d1, d2, d3, d4, d5, d6, d7, en, U8G_PIN_NONE, U8G_PIN_NONE, di, rw, reset); // cs1 = cs2 = U8G_PIN_NONE
  }
};


class U8GLIB_LC7981_160X80 : public U8GLIB {
public:
  U8GLIB_LC7981_160X80() : U8GLIB() { }
  U8GLIB_LC7981_160X80(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                       uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, di, rw, reset);
  }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_lc7981_160x80_8bit, d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, U8G_PIN_NONE, di, rw, reset);
  }
};

class U8GLIB_LC7981_240X64 : public U8GLIB {
public:
  U8GLIB_LC7981_240X64() : U8GLIB() { }
  U8GLIB_LC7981_240X64(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                       uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, di, rw, reset);
  }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_lc7981_240x64_8bit, d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, U8G_PIN_NONE, di, rw, reset);
  }
};

class U8GLIB_LC7981_240X128 : public U8GLIB {
public:
  U8GLIB_LC7981_240X128() : U8GLIB() { }
  U8GLIB_LC7981_240X128(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                        uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, di, rw, reset);
  }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_lc7981_240x128_8bit, d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, U8G_PIN_NONE, di, rw, reset);
  }
};

// 16 bit mode required: Remove comment from "#define U8G_16BIT 1" in utility/u8g.h
class U8GLIB_LC7981_320X64 : public U8GLIB {
public:
  U8GLIB_LC7981_320X64() : U8GLIB() { }
  U8GLIB_LC7981_320X64(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                       uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, di, rw, reset);
  }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                       uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_lc7981_320x64_8bit, d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, U8G_PIN_NONE, di, rw, reset);
  }
};


class U8GLIB_DOGXL160_BW : public U8GLIB {
public:
  U8GLIB_DOGXL160_BW() : U8GLIB() { }
  U8GLIB_DOGXL160_BW(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_DOGXL160_BW(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1610_dogxl160_bw_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1610_dogxl160_bw_hw_spi, cs, a0, reset); }
};

class U8GLIB_DOGXL160_GR : public U8GLIB {
public:
  U8GLIB_DOGXL160_GR() : U8GLIB() { }
  U8GLIB_DOGXL160_GR(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_DOGXL160_GR(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1610_dogxl160_gr_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1610_dogxl160_gr_hw_spi, cs, a0, reset); }
};

class U8GLIB_DOGXL160_2X_BW : public U8GLIB {
public:
  U8GLIB_DOGXL160_2X_BW() : U8GLIB() { }
  U8GLIB_DOGXL160_2X_BW(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_DOGXL160_2X_BW(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1610_dogxl160_2x_bw_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1610_dogxl160_2x_bw_hw_spi, cs, a0, reset); }
};

class U8GLIB_DOGXL160_2X_GR : public U8GLIB {
public:
  U8GLIB_DOGXL160_2X_GR() : U8GLIB() { }
  U8GLIB_DOGXL160_2X_GR(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_DOGXL160_2X_GR(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1610_dogxl160_2x_gr_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_uc1610_dogxl160_2x_gr_hw_spi, cs, a0, reset); }
};


class U8GLIB_NHD27OLED_BW : public U8GLIB {
public:
  U8GLIB_NHD27OLED_BW() : U8GLIB() { }
  U8GLIB_NHD27OLED_BW(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_NHD27OLED_BW(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_NHD27OLED_BW(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                      uint8_t cs, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, cs, di, rw, reset);
  }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1325_nhd27oled_bw_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1325_nhd27oled_bw_hw_spi, cs, a0, reset); }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t cs, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_ssd1325_nhd27oled_bw_parallel, d0, d1, d2, d3, d4, d5, d6, d7, U8G_PIN_NONE, cs, U8G_PIN_NONE, di, rw, reset);
  }
};

class U8GLIB_NHD27OLED_2X_BW : public U8GLIB {
public:
  U8GLIB_NHD27OLED_2X_BW() : U8GLIB() { }
  U8GLIB_NHD27OLED_2X_BW(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_NHD27OLED_2X_BW(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_NHD27OLED_2X_BW(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                         uint8_t cs, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, cs, di, rw, reset);
  }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1325_nhd27oled_2x_bw_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1325_nhd27oled_2x_bw_hw_spi, cs, a0, reset); }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t cs, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_ssd1325_nhd27oled_2x_bw_parallel, d0, d1, d2, d3, d4, d5, d6, d7, U8G_PIN_NONE, cs, U8G_PIN_NONE, di, rw, reset);
  }
};

class U8GLIB_NHD31OLED_BW : public U8GLIB {
public:
  U8GLIB_NHD31OLED_BW() : U8GLIB() { }
  U8GLIB_NHD31OLED_BW(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_NHD31OLED_BW(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_NHD31OLED_BW(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                      uint8_t cs, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, cs, di, rw, reset);
  }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1322_nhd31oled_bw_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1322_nhd31oled_bw_hw_spi, cs, a0, reset); }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t cs, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_ssd1322_nhd31oled_bw_parallel, d0, d1, d2, d3, d4, d5, d6, d7, U8G_PIN_NONE, cs, U8G_PIN_NONE, di, rw, reset);
  }
};

class U8GLIB_NHD31OLED_2X_BW : public U8GLIB {
public:
  U8GLIB_NHD31OLED_2X_BW() : U8GLIB() { }
  U8GLIB_NHD31OLED_2X_BW(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_NHD31OLED_2X_BW(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1322_nhd31oled_2x_bw_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1322_nhd31oled_2x_bw_hw_spi, cs, a0, reset); }
};

class U8GLIB_NHD31OLED_GR : public U8GLIB {
public:
  U8GLIB_NHD31OLED_GR() : U8GLIB() { }
  U8GLIB_NHD31OLED_GR(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_NHD31OLED_GR(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_NHD31OLED_GR(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                      uint8_t cs, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, cs, di, rw, reset);
  }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1322_nhd31oled_gr_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1322_nhd31oled_gr_hw_spi, cs, a0, reset); }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t cs, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_ssd1322_nhd31oled_gr_parallel, d0, d1, d2, d3, d4, d5, d6, d7, U8G_PIN_NONE, cs, U8G_PIN_NONE, di, rw, reset);
  }
};

class U8GLIB_NHD31OLED_2X_GR : public U8GLIB {
public:
  U8GLIB_NHD31OLED_2X_GR() : U8GLIB() { }
  U8GLIB_NHD31OLED_2X_GR(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_NHD31OLED_2X_GR(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1322_nhd31oled_2x_gr_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1322_nhd31oled_2x_gr_hw_spi, cs, a0, reset); }
};


class U8GLIB_SSD1306_128X64 : public U8GLIB {
public:
  U8GLIB_SSD1306_128X64() : U8GLIB() { }
  U8GLIB_SSD1306_128X64(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_SSD1306_128X64(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_SSD1306_128X64(uint8_t options) { init(options); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1306_128x64_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1306_128x64_hw_spi, cs, a0, reset); }
  void init(uint8_t options = U8G_I2C_OPT_NONE) { U8GLIB::init(&u8g_dev_ssd1306_128x64_i2c, options); }
};

class U8GLIB_SSD1306_ADAFRUIT_128X64 : public U8GLIB {
public:
  U8GLIB_SSD1306_ADAFRUIT_128X64() : U8GLIB() { }
  U8GLIB_SSD1306_ADAFRUIT_128X64(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_SSD1306_ADAFRUIT_128X64(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_SSD1306_ADAFRUIT_128X64(uint8_t options) { init(options); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1306_adafruit_128x64_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1306_adafruit_128x64_hw_spi, cs, a0, reset); }
  void init(uint8_t options = U8G_I2C_OPT_NONE) { U8GLIB::init(&u8g_dev_ssd1306_adafruit_128x64_i2c, options); }
};


class U8GLIB_SSD1306_128X64_2X : public U8GLIB {
public:
  U8GLIB_SSD1306_128X64_2X() : U8GLIB() { }
  U8GLIB_SSD1306_128X64_2X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_SSD1306_128X64_2X(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_SSD1306_128X64_2X(uint8_t options) { init(options); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1306_128x64_2x_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1306_128x64_2x_hw_spi, cs, a0, reset); }
  void init(uint8_t options = U8G_I2C_OPT_NONE) { U8GLIB::init(&u8g_dev_ssd1306_128x64_2x_i2c, options); }
};

class U8GLIB_SH1106_128X64 : public U8GLIB {
public:
  U8GLIB_SH1106_128X64() : U8GLIB() { }
  U8GLIB_SH1106_128X64(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_SH1106_128X64(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_SH1106_128X64(uint8_t options) { init(options); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_sh1106_128x64_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_sh1106_128x64_hw_spi, cs, a0, reset); }
  void init(uint8_t options = U8G_I2C_OPT_NONE) { U8GLIB::init(&u8g_dev_ssd1306_128x64_2x_i2c, options); }
};

class U8GLIB_SH1106_128X64_2X : public U8GLIB {
public:
  U8GLIB_SH1106_128X64_2X() : U8GLIB() { }
  U8GLIB_SH1106_128X64_2X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_SH1106_128X64_2X(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_SH1106_128X64_2X(uint8_t options) { init(options); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_sh1106_128x64_2x_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_sh1106_128x64_2x_hw_spi, cs, a0, reset); }
  void init(uint8_t options = U8G_I2C_OPT_NONE) { U8GLIB::init(&u8g_dev_sh1106_128x64_2x_i2c, options); }
};

class U8GLIB_SSD1309_128X64 : public U8GLIB {
public:
  U8GLIB_SSD1309_128X64() : U8GLIB() { }
  U8GLIB_SSD1309_128X64(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_SSD1309_128X64(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_SSD1309_128X64(uint8_t options) { init(options); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1309_128x64_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1309_128x64_hw_spi, cs, a0, reset); }
  void init(uint8_t options = U8G_I2C_OPT_NONE) { U8GLIB::init(&u8g_dev_ssd1309_128x64_i2c, options); }
};

class U8GLIB_SSD1306_128X32 : public U8GLIB {
public:
  U8GLIB_SSD1306_128X32() : U8GLIB() { }
  U8GLIB_SSD1306_128X32(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_SSD1306_128X32(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_SSD1306_128X32(uint8_t options) { init(options); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1306_128x32_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1306_128x32_hw_spi, cs, a0, reset); }
  void init(uint8_t options = U8G_I2C_OPT_NONE) { U8GLIB::init(&u8g_dev_ssd1306_128x32_i2c, options); }
};

class U8GLIB_SSD1306_128X32_2X : public U8GLIB {
public:
  U8GLIB_SSD1306_128X32_2X() : U8GLIB() { }
  U8GLIB_SSD1306_128X32_2X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_SSD1306_128X32_2X(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_SSD1306_128X32_2X(uint8_t options) { init(options); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1306_128x32_2x_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1306_128x32_2x_hw_spi, cs, a0, reset); }
  void init(uint8_t options = U8G_I2C_OPT_NONE) { U8GLIB::init(&u8g_dev_ssd1306_128x32_2x_i2c, options); }
};

class U8GLIB_SSD1306_64X48 : public U8GLIB {
public:
  U8GLIB_SSD1306_64X48() : U8GLIB() { }
  U8GLIB_SSD1306_64X48(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_SSD1306_64X48(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_SSD1306_64X48(uint8_t options) { init(options); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1306_64x48_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1306_64x48_hw_spi, cs, a0, reset); }
  void init(uint8_t options = U8G_I2C_OPT_NONE) { U8GLIB::init(&u8g_dev_ssd1306_64x48_i2c, options); }
};

class U8GLIB_SSD1306_64X48_2X : public U8GLIB {
public:
  U8GLIB_SSD1306_64X48_2X() : U8GLIB() { }
  U8GLIB_SSD1306_64X48_2X(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_SSD1306_64X48_2X(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_SSD1306_64X48_2X(uint8_t options) { init(options); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1306_64x48_2x_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1306_64x48_2x_hw_spi, cs, a0, reset); }
  void init(uint8_t options = U8G_I2C_OPT_NONE) { U8GLIB::init(&u8g_dev_ssd1306_64x48_2x_i2c, options); }
};


class U8GLIB_NHD27OLED_GR : public U8GLIB {
public:
  U8GLIB_NHD27OLED_GR() : U8GLIB() { }
  U8GLIB_NHD27OLED_GR(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_NHD27OLED_GR(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1325_nhd27oled_gr_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1325_nhd27oled_gr_hw_spi, cs, a0, reset); }
};

class U8GLIB_NHD27OLED_2X_GR : public U8GLIB {
public:
  U8GLIB_NHD27OLED_2X_GR() : U8GLIB() { }
  U8GLIB_NHD27OLED_2X_GR(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_NHD27OLED_2X_GR(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1325_nhd27oled_2x_gr_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1325_nhd27oled_2x_gr_hw_spi, cs, a0, reset); }
};

class U8GLIB_SSD1327_96X96_GR : public U8GLIB {
public:
  U8GLIB_SSD1327_96X96_GR() : U8GLIB() { }
  U8GLIB_SSD1327_96X96_GR(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_SSD1327_96X96_GR(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_SSD1327_96X96_GR(uint8_t options) { init(options); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1327_96x96_gr_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1327_96x96_gr_hw_spi, cs, a0, reset); }
  void init(uint8_t options = U8G_I2C_OPT_NONE) { U8GLIB::init(&u8g_dev_ssd1327_96x96_gr_i2c, options); }
};

class U8GLIB_SSD1327_96X96_2X_GR : public U8GLIB {
public:
  U8GLIB_SSD1327_96X96_2X_GR() : U8GLIB() { }
  U8GLIB_SSD1327_96X96_2X_GR(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_SSD1327_96X96_2X_GR(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_SSD1327_96X96_2X_GR(uint8_t options) { init(options); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1327_96x96_2x_gr_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1327_96x96_2x_gr_hw_spi, cs, a0, reset); }
  void init(uint8_t options = U8G_I2C_OPT_NONE) { U8GLIB::init(&u8g_dev_ssd1327_96x96_2x_gr_i2c, options); }
};

/*
class U8GLIB_LD7032_60x32 : public U8GLIB {
public:
  U8GLIB_LD7032_60x32() : U8GLIB() { }
  U8GLIB_LD7032_60x32(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_LD7032_60x32(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  U8GLIB_LD7032_60x32(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                      uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, di, rw, reset);
  }
  U8GLIB_LD7032_60x32(uint8_t options) { init(options); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ld7032_60x32_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ld7032_60x32_hw_spi, cs, a0, reset); }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_ld7032_60x32_parallel, d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, U8G_PIN_NONE, di, rw, reset);
  }
  void init(uint8_t options = U8G_I2C_OPT_NONE) { U8GLIB::init(&u8g_dev_ld7032_60x32_i2c, options); }
};

*/

class U8GLIB_HT1632_24X16 : public U8GLIB {
public:
  U8GLIB_HT1632_24X16() : U8GLIB() { }
  U8GLIB_HT1632_24X16(uint8_t wr, uint8_t data, uint8_t cs) { init(wr, data, cs); }
  void init(uint8_t wr, uint8_t data, uint8_t cs) { U8GLIB::init(&u8g_dev_ht1632_24x16, wr, data, cs, U8G_PIN_NONE, U8G_PIN_NONE); }
};



class U8GLIB_PCF8812 : public U8GLIB {
public:
  U8GLIB_PCF8812() : U8GLIB() { }
  U8GLIB_PCF8812(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_PCF8812(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_pcf8812_96x65_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_pcf8812_96x65_hw_spi, cs, a0, reset); }
};

class U8GLIB_PCD8544 : public U8GLIB {
public:
  U8GLIB_PCD8544() : U8GLIB() { }
  U8GLIB_PCD8544(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_PCD8544(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_pcd8544_84x48_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_pcd8544_84x48_hw_spi, cs, a0, reset); }
};

class U8GLIB_TLS8204_84X48 : public U8GLIB {
public:
  U8GLIB_TLS8204_84X48() : U8GLIB() { }
  U8GLIB_TLS8204_84X48(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_tls8204_84x48_sw_spi, sck, mosi, cs, a0, reset); }
};

class U8GLIB_KS0108_128 : public U8GLIB {
public:
  U8GLIB_KS0108_128() : U8GLIB() { }
  U8GLIB_KS0108_128(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                    uint8_t en, uint8_t cs1, uint8_t cs2, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, cs2, di, rw, reset);
  }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t cs1, uint8_t cs2, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_ks0108_128x64_fast, d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, cs2, di, rw, reset);
  }
};

class U8GLIB_SBN1661_122X32 : public U8GLIB {
public:
  U8GLIB_SBN1661_122X32() : U8GLIB() { }
  U8GLIB_SBN1661_122X32(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                        uint8_t cs1, uint8_t cs2, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, cs1, cs2, di, rw, reset);
  }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                        uint8_t cs1, uint8_t cs2, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_sbn1661_122x32, d0, d1, d2, d3, d4, d5, d6, d7, U8G_PIN_NONE, cs1, cs2, di, rw, reset);
  }
};

class U8GLIB_T6963_240X128 : public U8GLIB {
public:
  U8GLIB_T6963_240X128() : U8GLIB() { }
  U8GLIB_T6963_240X128(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                       uint8_t cs, uint8_t a0, uint8_t wr, uint8_t rd, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, cs, a0, wr, rd, reset);
  }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t cs, uint8_t a0, uint8_t wr, uint8_t rd, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_t6963_240x128_8bit, d0, d1, d2, d3, d4, d5, d6, d7, cs, a0, wr, rd, reset);
  }
};

class U8GLIB_T6963_128X128 : public U8GLIB {
public:
  U8GLIB_T6963_128X128() : U8GLIB() { }
  U8GLIB_T6963_128X128(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                       uint8_t cs, uint8_t a0, uint8_t wr, uint8_t rd, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, cs, a0, wr, rd, reset);
  }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t cs, uint8_t a0, uint8_t wr, uint8_t rd, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_t6963_128x128_8bit, d0, d1, d2, d3, d4, d5, d6, d7, cs, a0, wr, rd, reset);
  }
};

class U8GLIB_T6963_240X64 : public U8GLIB {
public:
  U8GLIB_T6963_240X64() : U8GLIB() { }
  U8GLIB_T6963_240X64(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                      uint8_t cs, uint8_t a0, uint8_t wr, uint8_t rd, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, cs, a0, wr, rd, reset);
  }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t cs, uint8_t a0, uint8_t wr, uint8_t rd, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_t6963_240x64_8bit, d0, d1, d2, d3, d4, d5, d6, d7, cs, a0, wr, rd, reset);
  }
};

class U8GLIB_T6963_128X64 : public U8GLIB {
public:
  U8GLIB_T6963_128X64() : U8GLIB() { }
  U8GLIB_T6963_128X64(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                      uint8_t cs, uint8_t a0, uint8_t wr, uint8_t rd, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, cs, a0, wr, rd, reset);
  }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t cs, uint8_t a0, uint8_t wr, uint8_t rd, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_t6963_128x64_8bit, d0, d1, d2, d3, d4, d5, d6, d7, cs, a0, wr, rd, reset);
  }
};


class U8GLIB_ST7687_C144MVGD: public U8GLIB {
public:
  U8GLIB_ST7687_C144MVGD() : U8GLIB() { }
  U8GLIB_ST7687_C144MVGD(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) {
    init(sck, mosi, cs, a0, reset);
  }
  U8GLIB_ST7687_C144MVGD(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                         uint8_t en, uint8_t cs, uint8_t a0, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, cs, a0, rw, reset);
  }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_st7687_c144mvgd_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                         uint8_t en, uint8_t cs, uint8_t a0, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_ks0108_128x64_fast, d0, d1, d2, d3, d4, d5, d6, d7, en, cs, U8G_PIN_NONE, a0, rw, reset);
  }
};

class U8GLIB_ILI9325D_320x240 : public U8GLIB {
public:
  U8GLIB_ILI9325D_320x240() : U8GLIB() { }
  /*
  U8GLIB_ILI9325D_320x240(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                          uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, di, rw, reset);
  }
  void init(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_ili9325d_320x240_8bit, d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, U8G_PIN_NONE, di, rw, reset);
  }
  */
  U8GLIB_ILI9325D_320x240(uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    init(en, cs1, di, rw, reset);
  }
  void init(uint8_t en, uint8_t cs1, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE) {
    (void)init8BitFixedPort(&u8g_dev_ili9325d_320x240_8bit, en, cs1, di, rw, reset);
  }
};


class U8GLIB_SSD1351_128X128_332 : public U8GLIB {
public:
  U8GLIB_SSD1351_128X128_332() : U8GLIB() { }
  U8GLIB_SSD1351_128X128_332(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_SSD1351_128X128_332(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1351_128x128_332_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1351_128x128_332_hw_spi, cs, a0, reset); }
};

class U8GLIB_SSD1351_128X128_4X_332 : public U8GLIB {
public:
  U8GLIB_SSD1351_128X128_4X_332() : U8GLIB() { }
  U8GLIB_SSD1351_128X128_4X_332(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_ssd1351_128x128_4x_332_sw_spi, sck, mosi, cs, a0, reset);
  }
  U8GLIB_SSD1351_128X128_4X_332(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) {
    U8GLIB::init(&u8g_dev_ssd1351_128x128_4x_332_hw_spi, cs, a0, reset);
  }
};

class U8GLIB_SSD1351_128X128GH_332 : public U8GLIB {
public:
  U8GLIB_SSD1351_128X128GH_332() : U8GLIB() { }
  U8GLIB_SSD1351_128X128GH_332(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_SSD1351_128X128GH_332(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1351_128x128gh_332_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1351_128x128gh_332_hw_spi, cs, a0, reset); }
};

class U8GLIB_SSD1351_128X128GH_4X_332 : public U8GLIB {
public:
  U8GLIB_SSD1351_128X128GH_4X_332() : U8GLIB() { }
  U8GLIB_SSD1351_128X128GH_4X_332(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_SSD1351_128X128GH_4X_332(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1351_128x128gh_4x_332_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1351_128x128gh_4x_332_hw_spi, cs, a0, reset); }
};

class U8GLIB_SSD1351_128X128_IDX : public U8GLIB {
public:
  U8GLIB_SSD1351_128X128_IDX() : U8GLIB() { }
  U8GLIB_SSD1351_128X128_IDX(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_SSD1351_128X128_IDX(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1351_128x128_idx_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1351_128x128_idx_hw_spi, cs, a0, reset); }
};

class U8GLIB_SSD1351_128X128_HICOLOR : public U8GLIB {
public:
  U8GLIB_SSD1351_128X128_HICOLOR() : U8GLIB() { }
  U8GLIB_SSD1351_128X128_HICOLOR(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_SSD1351_128X128_HICOLOR(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1351_128x128_hicolor_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1351_128x128_hicolor_hw_spi, cs, a0, reset); }
};

class U8GLIB_SSD1351_128X128_4X_HICOLOR : public U8GLIB {
public:
  U8GLIB_SSD1351_128X128_4X_HICOLOR() : U8GLIB() { }
  U8GLIB_SSD1351_128X128_4X_HICOLOR(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_SSD1351_128X128_4X_HICOLOR(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1351_128x128_4x_hicolor_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1351_128x128_4x_hicolor_hw_spi, cs, a0, reset); }
};

class U8GLIB_SSD1351_128X128GH_HICOLOR : public U8GLIB {
public:
  U8GLIB_SSD1351_128X128GH_HICOLOR() : U8GLIB() { }
  U8GLIB_SSD1351_128X128GH_HICOLOR(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_SSD1351_128X128GH_HICOLOR(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1351_128x128gh_hicolor_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1351_128x128gh_hicolor_hw_spi, cs, a0, reset); }
};

class U8GLIB_SSD1351_128X128GH_4X_HICOLOR : public U8GLIB {
public:
  U8GLIB_SSD1351_128X128GH_4X_HICOLOR() : U8GLIB() { }
  U8GLIB_SSD1351_128X128GH_4X_HICOLOR(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(sck, mosi, cs, a0, reset); }
  U8GLIB_SSD1351_128X128GH_4X_HICOLOR(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { init(cs, a0, reset); }
  void init(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1351_128x128gh_4x_hicolor_sw_spi, sck, mosi, cs, a0, reset); }
  void init(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) { U8GLIB::init(&u8g_dev_ssd1351_128x128gh_4x_hicolor_hw_spi, cs, a0, reset); }
};


class U8GLIB_FLIPDISC_2X7 : public U8GLIB {
public:
  U8GLIB_FLIPDISC_2X7() { }
  void init() { U8GLIB::init(&u8g_dev_flipdisc_2x7); }
};

class U8GLIB_VS : public U8GLIB {
public:
  U8GLIB_VS() { }
  void init() { U8GLIB::init(&u8g_dev_vs); }
};

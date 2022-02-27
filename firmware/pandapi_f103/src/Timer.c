/*
 * This file is part of the 碌OS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "Timer.h"
#include "cortexm/ExceptionHandlers.h"

// ----------------------------------------------------------------------------

#if defined(USE_HAL_DRIVER)
void HAL_IncTick(void);
#endif

// Forward declarations.

void
timer_tick (void);
float  get_pid_output(int e);

// ----------------------------------------------------------------------------

volatile timer_ticks_t timer_delayCount;

// ----------------------------------------------------------------------------

void
timer_start (void)
{
  // Use SysTick as reference for the delay loops.
  SysTick_Config (SystemCoreClock / TIMER_FREQUENCY_HZ);
}

void
timer_sleep (timer_ticks_t ticks)
{
  timer_delayCount = ticks;

  // Busy wait until the SysTick decrements the counter to zero.
  while (timer_delayCount != 0u)
    ;
}

void
timer_tick (void)
{
  // Decrement to zero the counter used by the delay routine.
  if (timer_delayCount != 0u)
    {
      --timer_delayCount;
    }
}

// ----- SysTick_Handler() ----------------------------------------------------

void
SysTick_Handler (void)
{
#if defined(USE_HAL_DRIVER)
  HAL_IncTick();
#endif
  timer_tick ();
}


  float gt[5]={64.0};
__IO u16 Read_ADC_Raw[32][3] ;
const u16 Temperature_Table_B3950[] =
{
		 4038,
		 4035,//0
		 4032,
		 4029,
		 4025,
		 4022,
		 4019,
		 4015,
		 4011,
		 4007,
		 4003,
		 3998,//10
		 3993,
		 3989,
		 3984,
		 3979,
		 3973,
		 3968,
		 3962,
		 3956,
		 3949,
		 3942,//20
		 3935,
		 3928,
		 3920,
		 3912,
		 3904,
		 3894,//3896,
		 3888,//			 27c
		 3881,
		 3874,
		 3865, //30
		 3856,
		 3847,
		 3836,
		 3826,
		 3814,//		   35c

		 3803,
		 3790,
		 3777,
		 3764,//	 array_num 40
		 3750,//  40c

		 3737,
		 3723,
		 3710,
		 3704,//3698,
		 3698,//3683,
		 3683,//3668,
		 3668,//3653,
		 3653,//3637,
		 3637,//3622,
		 3622,//3606,	  50c

		 3606,//3589,
		 3589,//3573,
		 3573,//3555,
		 3555,//3538,
		 3538,//3520,	  55c

		 3520,//3501,
		 3501,//3481,
		 3481,//3461,
		 3461,//3439,		   array_num60
			 3439,//3419,	   60c

		 3429,//3398,
		 3419,//3376,
		 3398,//3354,
		 3376,//3331,
		 3354,//3308,	   65c

		 3331,//3284,
		 3308,//3260,
		 3284,//3236,
		 3260,//3211,
			 3236,//3187,	  70c

		 3211, //3161,
		 3187, //3136,
		 3161,//3111,
		 3136,//3086,
		 3123,//3061,

		 3111,//3036,
		 3086,//3010,	   77c
		 3061,//2985,
		 3036,//2959,
		 3010,//2933,	   80c

		 2985,//2907,
		 2959, //2880,
		 2933, //2853,
		 2907,//2824,
		 2880,//2796,	  85c


		 2853,//2766,
		 2824,//2736,
		 2796,//2704,
		 2766,//2672,
		 2751,//2641,

		 2736,//2611,// 	91C
		 2704,//2581,
		 2672,//2551,
		 2641,//2522,

		 2611,//2492,// 	 95C
		 2581,//2463,
		 2551,//2433,
		 2522,//2403,
		 2507,//2372,
		 2492,//2341,// 	 100c

		 2463,//2309,
		 2433,//2276,
		 2403,//2242,
		 2372,//2208,
		 2341,//2180,// 	  105c


		 2309,//2150,
		 2276,//2120,
		 2242,//2090,
		 2208,//2058,
		 2194,//2027,		110c

		 2180,//1995,
		 2165,//1964,
		 2150,//1932,
			 2120,//1901,
		 2090,//1871,
		 2058,//1842,
		 2042,//1814,
		 2027,//1787,
		 1995,//1761,
		 1964,//1731,// 	 120c

		 1932,//1702,
		 1901,//1674,
		 1871,//1647,
		 1842,//1621,
		 1828,//1596,

		 1814,//1571,
		 1800,//1547,
		 1787,//1523,// 	128c
		 1761,//1499,
		 1731,//1475,

		 1702,//1451,
		 1674,//1426,
		 1647,//1401,
		 1621,//1375,
		 1596,//1348,
		 1571,//1323,
		 1547,//1298,
		 1523,//1273,
		 1499,//1250,
		 1475,//1227,// 	140c

		 1451,//1205,
		 1426,//1184,
		 1401,//1164,
		 1375,//1144,
		 1348,//1125,// 	145c

		 1323,//1107,
		 1298,//1090,
		 1273,//1073,
		 1250,//1057,
		 1227,//1035,	   150c

		 1205,//1014,
		 1184,//994,
		 1164,//975,
		 1144,//957,
		 1125,//940,//	   155c

		 1107,//924,
		 1090,//908,
		 1073,//892,
		 1057,//876,
		 1035,//861, 160
		 1014,//845,
		 994,//829,
		 975,//813,
		 957,//797,
		 940,//782, //	  165c

		 924,//768,
		 908,//754,
		 892,//740,
		 876,//727,
		 861,//713,
		 829,//701,
		 813,//688,
		 797,//676,
		 782,//664,
		 768,//652,//	  175c

		 754,//641,
		 740,//629,
		 727,//618,
		 713,//607,
		 701,//594, 	 180C

		 688,//583,
		 676,//572,
		 664,//562,
		 652,//552,
		 641,//543,
		 629,//535,
		 618,//526,
		 607,//518,
		 594,//509,
		 583,//501, 	  190C

		 572,//493,
		 562,//484,
		 552,//475,
		 543,//465,
		 535,//458,
		 526,//451,
		 518,//444,
		 509,//436,
		 501,//428,
		 493,//420, 	   200C

		 484,//412,
		 475,//404,
		 465,//396,
		 458,//389,
		 451,//381,
		 444,//374,
		 436,//368,
		 428,//361,
		 420,//356,
		 412,//349, 	  210C

		 404,//343,
		 396,//337,
		 389,//332,
		 381,//326,
		 374,//320,
		 368,//314,
		 361,//309,
		 356,//304,
		 349,//298,
		 343,//293, 	 220C

		 337,//288,
		 332,//283,
		 326,//278,
		 320,//273,
		 314,//269,
		 309,//265,
		 304,//260,
		 298,//256,
		 293,//251,
		 288,//247,//		 230C

		 283,//243,
		 278,//238,
		 273,//234,
		 269,//230,
		 265,//226,
		 260,//222,
		 256,//219,
		 251,//215,
		 247,//212,
		 243,//208,//		240C

		 238,//205,
		 234,//202,
		 230,//199,
		 226,//196,
		 222,//193,
		 219,//190,
		 215,//187,
		 212,//184,
		 208,//181,
		 205,//178,//	   250C

		 202,//174,
		 199,//172,
		 196,//170,
		 193,//166,
		 190,//164,
		 187,//162,
		 184,//159,
		 181,//157,
		 178,//154,
		 174,//152,//		260C

		 172,//150,
		 170,//147,
		 166,//145,
		 164,//142,
		 162,//140,
		 159,//137,
		 157,//136,
		 154,//134,
		 152,//132,
		 150,//130, 	   270c

		 147,//128,
		 145,//126,
		 142,//123,
		 140,//122,
		 137,//120,
		 136,//118,
		 134,//116,
		 132,//114,
		 130,//113,
		 128,//111, 	   280c

		 126,//109,
		 123,//108,
		 122,//106,
		 120,//105,
		 118,//103,
		 116,//101,
		 114,//100,
		 113,//98,
		 111,//96,
		 109,//95,		  290c

		 108,//93,
		 106,//91,
		 105,//90,
		 103,//88,
		 101,//87,
		 100,//86,
		 98,//85,
		 96,//84,
		 93,//83,

	 };

typedef signed short int16_t;

#define OVERSAMPLENR 1//16
#define OV(N)  (int16_t)((N)*(OVERSAMPLENR))
// { OV(93), 300 },
// R25 = 100 kOhm, beta25 = 4100 K, 4.7 kOhm pull-up, Hisens thermistor
const short temptable_13[][2]   = {

		 {4035,0},
		 {4032,1},
		 {4029,2},
		 {4025,3},
		 {4022,4},
		 {4019,5},
		 {4015,6},
		 {4011,7},
		 {4007,8},
		 {4003,9},
		 {3998,10},//10
		 {3993,11},
		 {3989,12},
		 {3984,13},
		 {3979,14},
		 {3973,15},
		 {3968,16},
		 {3962,17},
		 {3956,18},
		 {3949,19},
		 {3942,20},//20
		 {3935,21},
		 {3928,22},
		 {3920,23},
		 {3912,24},
		 {3904,25},
		 {3894,26},//3896,},
		 {3888,27},//			 {27c
		 {3881,28},
		 {3874,29},
		 {3865,30}, //30
		 {3856,31},
		 {3847,32},
		 {3836,33},
		 {3826,34},
		 {3814,35},//		   35c

		 {3803,36},
		 {3790,37},
		 {3777,38},
		 {3764,39},//	 array_num 40
		 {3750,40},//  40c

		 {3737,41},
		 {3723,42},
		 {3710,43},
		 {3704,44},//3698,},
		 {3698,45},//3683,},
		 {3683,46},//3668,},
		 {3668,47},//3653,},
		 {3653,48},//3637,},
		 {3637,49},//3622,},
		 {3622,50},//3606,},	  50c

		 {3606,51},//3589,},
		 {3589,52},//3573,},
		 {3573,53},//3555,},
		 {3555,54},//3538,},
		 {3538,55},//3520,},	  55c

		 {3520,56},//3501,},
		 {3501,57},//3481,},
		 {3481,58},//3461,},
		 {3461,59},//3439,},		   array_num60
			 {3439,60},//3419,},	   60c

		 {3429,61},//3398,},
		 {3419,62},//3376,},
		 {3398,63},//3354,},
		 {3376,64},//3331,},
		 {3354,65},//3308,},	   65c

		 {3331,66},//3284,},
		 {3308,67},//3260,},
		 {3284,68},//3236,},
		 {3260,69},//3211,},
			 {3236,70},//3187,},	  70c

		 {3211,71}, //3161,},
		 {3187,72}, //3136,},
		 {3161,73},//3111,},
		 {3136,74},//3086,},
		 {3123,75},//3061,},

		 {3111,76},//3036,},
		 {3086,77},//3010,},	   77c
		 {3061,78},//2985,},
		 {3036,79},//2959,},
		 {3010,80},//2933,},	   80c

		 {2985,81},//2907,},
		 {2959,82}, //2880,},
		 {2933,83}, //2853,},
		 {2907,84},//2824,},
		 {2880,85},//2796,},	  85c


		 {2853,86},//2766,},
		 {2824,87},//2736,},
		 {2796,88},//2704,},
		 {2766,89},//2672,},
		 {2751,90},//2641,},

		 {2736,91},//2611,},// 	91C
		 {2704,92},//2581,},
		 {2672,93},//2551,},
		 {2641,94},//2522,},

		 {2611,95},//2492,},// 	 95C
		 {2581,96},//2463,},
		 {2551,97},//2433,},
		 {2522,98},//2403,},
		 {2507,99},//2372,},
		 {2492,100},//2341,},// 	 100c

		 {2463,101},//2309,},
		 {2433,102},//2276,},
		 {2403,103},//2242,},
		 {2372,104},//2208,},
		 {2341,105},//2180,},// 	  105c


		 {2309,106},//2150,},
		 {2276,107},//2120,},
		 {2242,108},//2090,},
		 {2208,109},//2058,},
		 {2194,110},//2027,},		110c

		 {2180,111},//1995,},
		 {2165,112},//1964,},
		 {2150,113},//1932,},
			 {2120,114},//1901,},
		 {2090,115},//1871,},
		 {2058,116},//1842,},
		 {2042,117},//1814,},
		 {2027,118},//1787,},
		 {1995,119},//1761,},
		 {1964,120},//1731,},// 	 120c

		 {1932,121},//1702,},
		 {1901,122},//1674,},
		 {1871,123},//1647,},
		 {1842,124},//1621,},
		 {1828,125},//1596,},

		 {1814,126},//1571,},
		 {1800,126},//1547,},
		 {1787,128},//1523,},// 	128c
		 {1761,129},//1499,},
		 {1731,130},//1475,},

		 {1702,131},//1451,},
		 {1674,132},//1426,},
		 {1647,133},//1401,},
		 {1621,134,},//1375,},
		 {1596,135},//1348,},
		 {1571,136},//1323,},
		 {1547,137},//1298,},
		 {1523,138},//1273,},
		 {1499,139},//1250,},
		 {1475,140},//1227,},// 	140c

		 {1451,141},//1205,},
		 {1426,142},//1184,},
		 {1401,143},//1164,},
		 {1375,144},//1144,},
		 {1348,145},//1125,},// 	145c

		 {1323,146},//1107,},
		 {1298,147},//1090,},
		 {1273,148},//1073,},
		 {1250,149},//1057,},
		 {1227,150},//1035,},	   150c

		 {1205,151},//1014,},
		 {1184,152},//994,},
		 {1164,153},//975,},
		 {1144,154},//957,},
		 {1125,155},//940,},//	   155c

		 {1107,156},//924,},
		 {1090,157},//908,},
		 {1073,158},//892,},
		 {1057,159},//876,},
		 {1035,160},//861,}, 160
		 {1014,161},//845,},
		 {994,162},//829,},
		 {975,163},//813,},
		 {957,164},//797,},
		 {940,165},//782,}, //	  165c

		 {924,166},//768,},
		 {908,167},//754,},
		 {892,168},//740,},
		 {876,169},//727,},
		 {861,170},//713,},
		 {829,171},//701,},
		 {813,172},//688,},
		 {797,173},//676,},
		 {782,174},//664,},
		 {768,175},//652,},//	  175c

		 {754,176},//641,},
		 {740,177},//629,},
		 {727,178},//618,},
		 {713,179},//607,},
		 {701,180},//594,}, 	 180C

		 {688,181},//583,},
		 {676,182},//572,},
		 {664,183},//562,},
		 {652,184},//552,},
		 {641,185},//543,},
		 {629,186},//535,},
		 {618,187},//526,},
		 {607,188},//518,},
		 {594,189},//509,},
		 {583,190},//501,}, 	  190C

		 {572,191},//493,},
		 {562,192},//484,},
		 {552,193},//475,},
		 {543,194},//465,},
		 {535,195},//458,},
		 {526,196},//451,},
		 {518,197},//444,},
		 {509,198},//436,},
		 {501,199},//428,},
		 {493,200},//420,}, 	   200C

		 {484,201},//412,},
		 {475,202},//404,},
		 {465,203},//396,},
		 {458,204},//389,},
		 {451,205},//381,},
		 {444,206},//374,},
		 {436,207},//368,},
		 {428,208},//361,},
		 {420,209},//356,},
		 {412,210},//349,}, 	  210C

		 {404,211},//343,},
		 {396,212},//337,},
		 {389,213},//332,},
		 {381,214},//326,},
		 {374,215},//320,},
		 {368,216},//314,},
		 {361,217},//309,},
		 {356,218},//304,},
		 {349,219},//298,},
		 {343,220},//293,}, 	 220C

		 {337,221},//288,},
		 {332,222},//283,},
		 {326,223},//278,},
		 {320,224},//273,},
		 {314,225},//269,},
		 {309,226},//265,},
		 {304,227},//260,},
		 {298,228},//256,},
		 {293,229},//251,},
		 {288,230},//247,},//		 {230C

		 {283,231},//243,},
		 {278,232},//238,},
		 {273,233},//234,},
		 {269,234},//230,},
		 {265,235},//226,},
		 {260,236},//222,},
		 {256,237},//219,},
		 {251,238},//215,},
		 {247,239},//212,},
		 {243,240},//208,},//		240C

		 {238,241},//205,},
		 {234,242},//202,},
		 {230,243},//199,},
		 {226,244},//196,},
		 {222,245},//193,},
		 {219,246},//190,},
		 {215,247},//187,},
		 {212,248},//184,},
		 {208,249},//181,},
		 {205,250},//178,},//	   250C

		 {202,251},//174,},
		 {199,252},//172,},
		 {196,253},//170,},
		 {193,254},//166,},
		 {190,255},//164,},
		 {187,256},//162,},
		 {184,257},//159,},
		 {181,258},//157,},
		 {178,259},//154,},
		 {174,260},//152,},//		260C

		 {172,261},//150,},
		 {170,262},//147,},
		 {166,263},//145,},
		 {164,264},//142,},
		 {162,265},//140,},
		 {159,266},//137,},
		 {157,267},//136,},
		 {154,268},//134,},
		 {152,269},//132,},
		 {150,270},//130,}, 	   270c

		 {147,271},//128,},
		 {145,272},//126,},
		 {142,273},//123,},
		 {140,274},//122,},
		 {137,275},//120,},
		 {136,276},//118,},
		 {134,277},//116,},
		 {132,278},//114,},
		 {130,279},//113,},
		 {128,280},//111,}, 	   280c

		 {126,281},//109,},
		 {123,282},//108,},
		 {122,283},//106,},
		 {120,284},//105,},
		 {118,285},//103,},
		 {116,286},//101,},
		 {114,287},//100,},
		 {113,288},//98,},
		 {111,289},//96,},
		 {109,290},//95,},		  290c

		 {108,291},//93,},
		 {106,292},//91,},
		 {105,293},//90,},
		 {103,294},//88,},
		 {101,295},//87,},
		 {100,296},//86,},
		 {98,297},//85,},
		 {96,298},//84,},
		 {93,299}//83,},

	 };
/*
const short temptable_13[][2]   = {
  { OV(93), 300 },
  { OV(109), 290 },
  { OV(128), 280 },
  { OV(150), 270 },
  { OV(174), 260 },
  { OV(205), 250 },
  { OV(243), 240 },
  { OV(288), 230 },
  { OV(343), 220 },
  { OV(412), 210 },
  { OV(493), 200 },
  { OV(583), 190 },
  { OV(701), 180 },
  { OV(861), 170 },
  { OV(1035), 160 },
  { OV(1475), 140 },
  { OV(1964), 120 },
  { OV(2492), 100 },
  { OV(3010),  80 },
  { OV(3439),  60 },
  { OV(3750),  40 },
  { OV(3942),  20 },
  { OV(4035),   0 }
};
*/
/**
 * Bisect search for the range of the 'raw' value, then interpolate
 * proportionally between the under and over values.
 */
#define SCAN_THERMISTOR_TABLE(TBL,LEN) do{                             \
  uint8_t l = 0, r = LEN, m;                                           \
  for (;;) {                                                           \
    m = (l + r) >> 1;                                                  \
    if (m == l || m == r) return (short)pgm_read_word(&TBL[LEN-1][1]); \
    short v00 = pgm_read_word(&TBL[m-1][0]),                           \
          v10 = pgm_read_word(&TBL[m-0][0]);                           \
         if (raw < v00) r = m;                                         \
    else if (raw > v10) l = m;                                         \
    else {                                                             \
      const short v01 = (short)pgm_read_word(&TBL[m-1][1]),            \
                  v11 = (short)pgm_read_word(&TBL[m-0][1]);            \
      return v01 + (raw - v00) * float(v11 - v01) / float(v10 - v00);  \
    }                                                                  \
  }                                                                    \
}while(0)

#define pgm_read_word(b)  *b
//static void* heater_ttbl_map[3] = { (void*)HEATER_0_TEMPTABLE, (void*)HEATER_1_TEMPTABLE , (void*)HEATER_2_TEMPTABLE };
#define COUNT(a) (sizeof(a)/sizeof(*a))


/**********************************************************
***Function:     Get_Temperature
***Description: Get target current temperature
***Input:
***Output:
***Return:robert
***********************************************************/

float  Get_Temperature(u8 hot_heat_num)
{
#if 0
	int j=0;
	u16 temp=0;
	u32 temp_s=0;
	temp_s=0;
	for(j=0;j<32;j++)
	{
		temp_s+=Read_ADC_Raw[j][hot_heat_num];
	}
	int raw=temp_s/32;

	// Thermistor with conversion table?
	const short(*tt)[][2] = (short(*)[][2])(temptable_13);
	//SCAN_THERMISTOR_TABLE((*tt), heater_ttbllen_map[0]);
	int l = 0, r = COUNT(temptable_13), m,i;       
     
	 for(m=175;m<r-1;m++) 
	 {
	 
		 short v00 = pgm_read_word(&(*tt)[m+0][0]), 						 
			   v10 = pgm_read_word(&(*tt)[m+1][0]); 						 
	   if(raw>v10&&raw<v00)
	   {
	   
		 const short v01 = (short)pgm_read_word(&(*tt)[m+0][1]),			 
					 v11 = (short)pgm_read_word(&(*tt)[m+1][1]);			 
		   return v01 + (float)(v00-raw) / (float)(v00 - v10);
	   }
	 
	 }
	 
	 for(m=0;m<180;m++) 
	 {
	 
		 short v00 = pgm_read_word(&(*tt)[m+0][0]), 						 
			   v10 = pgm_read_word(&(*tt)[m+1][0]); 						 
	   if(raw>v10&&raw<v00)
	   {
	   
		 const short v01 = (short)pgm_read_word(&(*tt)[m+0][1]),			 
					 v11 = (short)pgm_read_word(&(*tt)[m+1][1]);			 
		   return v01 + (float)(v00-raw) / (float)(v00 - v10);
	   }
	 
	 }
	 
 return 0.0;
  for (;;) {                                                            
    m = (l + r) >> 1;                                                   
    if (m == l || m == r) return (short)pgm_read_word(&(*tt)[COUNT(temptable_13)-1][1]); 
    short v00 = pgm_read_word(&(*tt)[m-1][0]),                            
          v10 = pgm_read_word(&(*tt)[m-0][0]);                            
         if (raw > v00) r = m;                                         
    else if (raw < v10) l = m;                                          
    else {                                                              
      const short v01 = (short)pgm_read_word(&(*tt)[m-1][1]),             
                  v11 = (short)pgm_read_word(&(*tt)[m-0][1]);             
      return v01 + (v00-raw) * (float)(v01 - v11) / (float)(v00 - v10);
    }                                                                   
  }  
  
#else
   int j=0;
   u16 temp=0;
	u32 temp_s=0;
	temp_s=0;

	for(j=0;j<32;j++)
	{
		temp_s+=Read_ADC_Raw[j][hot_heat_num];
	}
	temp=temp_s/32;
	gt[hot_heat_num]=0;
	//////////////
	for(j=175;j<290;j++)
	{
		if((temp>=Temperature_Table_B3950[j+1])&&(temp<=Temperature_Table_B3950[j]))
		{
		
		   //const short v01 = (short)pgm_read_word(&(*tt)[m+0][1]), 			
			//		v11 = (short)pgm_read_word(&(*tt)[m+1][1]); 			
		//  return v01 + (float)(v00-raw) / (float)(v00 - v10);
			gt[hot_heat_num]=(float)(j)+(float)(Temperature_Table_B3950[j]-temp)/(Temperature_Table_B3950[j]-Temperature_Table_B3950[j+1]);
			return gt[hot_heat_num];

		}
	}
	for(j=0;j<180;j++)
	{
		if((temp>=Temperature_Table_B3950[j+1])&&(temp<=Temperature_Table_B3950[j]))
		{
			gt[hot_heat_num]=(float)(j)+(float)(Temperature_Table_B3950[j]-temp)/(Temperature_Table_B3950[j]-Temperature_Table_B3950[j+1]);
			return gt[hot_heat_num];
		}
	 }
	//////////////
   return gt[hot_heat_num];
#endif	
}


  void ADC_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)Read_ADC_Raw;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 3*32;   //dxc 应该是5
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);

	DMA_Cmd(DMA1_Channel1,ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);

    ADC_DeInit(ADC1);
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_NbrOfChannel =3;   //DXC 应该是5
	ADC_Init(ADC1,&ADC_InitStructure);

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);

/*
	ADC_RegularChannelConfig(ADC1,ADC_Channel_12,1,ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_11,2,ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_13,3,ADC_SampleTime_239Cycles5);
 	ADC_RegularChannelConfig(ADC1,ADC_Channel_10,4,ADC_SampleTime_239Cycles5);
*/
	ADC_RegularChannelConfig(ADC1,ADC_Channel_8,1,ADC_SampleTime_239Cycles5);//hotend0
	ADC_RegularChannelConfig(ADC1,ADC_Channel_9,2,ADC_SampleTime_239Cycles5);//bed
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_239Cycles5);//hotend1


	ADC_DMACmd(ADC1,ENABLE);

	ADC_Cmd(ADC1,ENABLE);


	//delay_ms(50);
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));

	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	 ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	 DMA_Cmd(DMA1_Channel1, ENABLE);

	 /////////////////////
	NVIC_InitTypeDef NVIC_InitStructure;
	/* Enable TIM2 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	/* Configure one bit for preemption priority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	/* Enable the TIM2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	//重新将Timer设置为缺省值
	TIM_DeInit(TIM2);
	//采用内部时钟给TIM2提供时钟源
	TIM_InternalClockConfig(TIM2);
	TIM_TimeBaseStructure.TIM_Prescaler = 720-1;//
	//设置时钟分割
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//设置计数器模式为向上计数模式
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//设置计数溢出大小，每计2000个数就产生一个更新事件
	TIM_TimeBaseStructure.TIM_Period = 100;//1ms
	//将配置应用到TIM2中
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	//清除溢出中断标志
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	//禁止ARR预装载缓冲器
	TIM_ARRPreloadConfig(TIM2, DISABLE);  //预装载寄存器的内容被立即传送到影子寄存器
	//开启TIM2的中断
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);	//开启定时器2

	  //////////////////////
}


  int e1,e2,e3,duk,uk;
  extruder_status Extruder;
  bed_status Bed_tmper;
  /******************************
       PID算法系数设置
  *******************************/
  void Pid_init()
  {
	Extruder.hightime[0]= 0;
	Extruder.hightime[1]= 0;
	e1 = 0;
	e2 = 0;
	e3 = 0;
	Extruder.kp[0] = 20;
	Extruder.ki[0] = 0.00026;
	Extruder.kd[0] = 3051.75;
	Extruder.kp[1] = 20;
	Extruder.ki[1] = 0.00026;
	Extruder.kd[1] = 3051.75;
  }
  
  
  char parse_string(char *src,char *start,char *end,char *out,int *e_pos)
  {
	  int i=0;
	  int s_index=-1;
	  int e_index=-1;
	  out[0]=0;
	  *e_pos=0;
	  for(i=0;i<strlen(src);i++)
	  {
		  if(strncmp(src+i,start,strlen(start))==0)
		  {
			  s_index=i+strlen(start);
			  break;
		  }
	  }
	  if(s_index<0)
		  return 1;
	  ///////////////////
	  if(strlen(end)==0)
	  {
		  strcpy(out,src+s_index);
		  *e_pos=strlen(src);
		  return 0;
  
	  }
	  for(i=s_index;i<strlen(src);i++)
	  {
		  if(strncmp(src+i,end,strlen(end))==0)
		  {
			  e_index=i;
			  break;
		  }
	  }   
	  if(e_index<0)
	  {
		  strcpy(out,src+s_index);
		  *e_pos=strlen(src);
		  return 0;
	  }
	  memcpy(out,src+s_index,e_index-s_index);
	  out[e_index-s_index]=0;
	  *e_pos=e_index;
	  return 2;
  }

  unsigned char pwm_count=0,soft_pwm_amount[2],auto_tune=0;
  /******************************
       温度比较  PID算法
  *******************************/  
  void pid_calc(void)
  {
      Extruder.kp[1]=Extruder.kp[0];
      Extruder.ki[1]=Extruder.ki[0];
      Extruder.kd[1]=Extruder.kd[0];
	  ////////
	  if(auto_tune!=1)
	  {
		  soft_pwm_amount[0] =	(int)get_pid_output(0) >> 1 ;
		  soft_pwm_amount[1] =	(int)get_pid_output(1) >> 1 ;
	  }
	  pwm_count++;
	  if (pwm_count >= 127) {
		  pwm_count = 0;
		  if(soft_pwm_amount[0]&&Extruder.rel_temper[0]>0)
			  GPIO_SetBits(GPIOB,GPIO_Pin_12);//hotend0 heat
		  else
			  GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		  if(soft_pwm_amount[1]&&Extruder.rel_temper[1]>0)
			  GPIO_SetBits(GPIOA,GPIO_Pin_12);//hotend1 heat
		  else
			  GPIO_ResetBits(GPIOA,GPIO_Pin_12);

	  }
	  else
	  {
		  if (soft_pwm_amount[0] <= pwm_count)
			  GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		 // else
		//	  GPIO_SetBits(GPIOB,GPIO_Pin_12);
		  if (soft_pwm_amount[1] <= pwm_count)
			  GPIO_ResetBits(GPIOA,GPIO_Pin_12);
		 // else
		//	  GPIO_SetBits(GPIOA,GPIO_Pin_12);
	  }
	 return; 	

  }
#define PIDTEMP
#define BANG_MAX 255     // Limits current to nozzle while in bang-bang mode; 255=full current
#define PID_MAX BANG_MAX // Limits current to nozzle while PID is active (see PID_FUNCTIONAL_RANGE below); 255=full current
#define PID_K1  0.95      // Smoothing factor within any PID loop
#define OVERSAMPLENR 16
#define MIN_ADC_ISR_LOOPS 10

#define ACTUAL_ADC_SAMPLES MAX(int(MIN_ADC_ISR_LOOPS), int(SensorsReady))
#define F_CPU   20000000

#define HOTEND_INDEX e
#define PID_K2 (1.0f-PID_K1)
/*#define PID_dT ((OVERSAMPLENR * float(ACTUAL_ADC_SAMPLES)) / (F_CPU / 64.0f / 256.0f))

// Apply the scale factors to the PID values
#define scalePID_i(i)	( (i) * float(PID_dT) )
#define unscalePID_i(i) ( (i) / float(PID_dT) )
#define scalePID_d(d)	( (d) / float(PID_dT) )
#define unscalePID_d(d) ( (d) * float(PID_dT) )*/
#define PID_FUNCTIONAL_RANGE 10 
#define true 1
#define false 0
float  get_pid_output(int e) 
{
	static float temp_iState[2],
				 temp_dState[2],
				 pTerm[2],
				 iTerm[2],
				 dTerm[2];
	
	
	static float pid_error[2];
	static char pid_reset[2];

    float pid_output;

	pid_error[HOTEND_INDEX] = Extruder.tar_temper[e]/10.0 - Extruder.rel_temper[e]/10.0;
	dTerm[HOTEND_INDEX] = PID_K2 * Extruder.kd[e] * (Extruder.rel_temper[e]/10.0 - temp_dState[HOTEND_INDEX]) + PID_K1 * dTerm[HOTEND_INDEX];
	temp_dState[HOTEND_INDEX] = Extruder.rel_temper[e]/10.0;

	if (pid_error[HOTEND_INDEX] > PID_FUNCTIONAL_RANGE) 
	{
		pid_output = BANG_MAX;
		pid_reset[HOTEND_INDEX] = true;
	}
	else if (pid_error[HOTEND_INDEX] < -(PID_FUNCTIONAL_RANGE) || Extruder.tar_temper[e]/10.0 == 0) 
	{
		pid_output = 0;
		pid_reset[HOTEND_INDEX] = true;
	}
	else
	{
		if (pid_reset[HOTEND_INDEX]) {
		  temp_iState[HOTEND_INDEX] = 0.0;
		  pid_reset[HOTEND_INDEX] = false;
		}
		pTerm[HOTEND_INDEX] = Extruder.kp[e] * pid_error[HOTEND_INDEX];
		temp_iState[HOTEND_INDEX] += pid_error[HOTEND_INDEX];
		iTerm[HOTEND_INDEX] = Extruder.ki[e] * temp_iState[HOTEND_INDEX];

		pid_output = pTerm[HOTEND_INDEX] + iTerm[HOTEND_INDEX] - dTerm[HOTEND_INDEX];


		if (pid_output > PID_MAX) {
		  if (pid_error[HOTEND_INDEX] > 0) temp_iState[HOTEND_INDEX] -= pid_error[HOTEND_INDEX]; // conditional un-integration
		  pid_output = PID_MAX;
		}
		else if (pid_output < 0) {
		  if (pid_error[HOTEND_INDEX] < 0) temp_iState[HOTEND_INDEX] -= pid_error[HOTEND_INDEX]; // conditional un-integration
		  pid_output = 0;
		}
	}
	  
  return pid_output;
}




// ----------------------------------------------------------------------------

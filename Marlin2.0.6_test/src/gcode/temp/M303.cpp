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

#include "../../inc/MarlinConfig.h"

#if HAS_PID_HEATING

#include "../gcode.h"
#include "../../lcd/ultralcd.h"
#include "../../module/temperature.h"

#if ENABLED(EXTENSIBLE_UI)
  #include "../../lcd/extui/ui_api.h"
#endif

/**
 * M303: PID relay autotune
 *
 *  S<temperature>  Set the target temperature. (Default: 150C / 70C)
 *  E<extruder>     Extruder number to tune, or -1 for the bed. (Default: E0)
 *  C<cycles>       Number of times to repeat the procedure. (Minimum: 3, Default: 5)
 *  U<bool>         Flag to apply the result to the current PID values
 *
 * With PID_DEBUG:
 *  D               Toggle PID debugging and EXIT without further action.
 */

#if ENABLED(PID_DEBUG)
  bool pid_debug_flag = 0;
#endif

void GcodeSuite::M303() {

  #if ENABLED(PID_DEBUG)
    if (parser.seen('D')) {
      pid_debug_flag = !pid_debug_flag;
      SERIAL_ECHO_START();
      SERIAL_ECHOPGM("PID Debug ");
      serialprintln_onoff(pid_debug_flag);
      return;
    }
  #endif

  #define SI TERN(PIDTEMPBED, H_BED, H_E0)
  #define EI TERN(PIDTEMP, HOTENDS - 1, H_BED)
  const heater_ind_t e = (heater_ind_t)parser.intval('E');
  if (!WITHIN(e, SI, EI)) {
    SERIAL_ECHOLNPGM(STR_PID_BAD_EXTRUDER_NUM);
    TERN_(EXTENSIBLE_UI, ExtUI::onPidTuning(ExtUI::result_t::PID_BAD_EXTRUDER_NUM));
    return;
  }

  const int c = parser.intval('C', 5);
  const bool u = parser.boolval('U');
  const int16_t temp = parser.celsiusval('S', e < 0 ? PREHEAT_1_TEMP_BED : PREHEAT_1_TEMP_HOTEND);

  #if DISABLED(BUSY_WHILE_HEATING)
    KEEPALIVE_STATE(NOT_BUSY);
  #endif

  ui.set_status(GET_TEXT(MSG_PID_AUTOTUNE));
 #if  PANDAPI 
	 ////////////////
	char tmp_data[32],cmd_buf[64],tmpe_k;
	int cn=0;
	unsigned int time_s_old=0;
	// char e=0;
	memset(tmp_data,0,sizeof(tmp_data));

	//////////P
	sprintf(tmp_data,"a E%d,C%d,U%d,S%d;\n",e,c,u,temp);
	printf(tmp_data);printf("\n");
	for(int i=0;i<strlen(tmp_data);i++)
		wiringPiI2CWriteReg8(i2c_fd, 8, tmp_data[i]);
	unsigned int kk=millis();

	memset(cmd_buf,0,sizeof(cmd_buf)); 

	SERIAL_ECHOPGM("PID autotune start\n");
				 
   while(1 )		   
	{
		tmpe_k=wiringPiI2CReadReg8(i2c_fd,8);
		if(tmpe_k!=0)
			cmd_buf[cn++]=tmpe_k;
		else
		{
			wiringPiI2CWriteReg8(i2c_fd, 8, '.');

		}

		   
		unsigned int time_s=millis();
		if((time_s-time_s_old)>5000)// 2 second
		{
			thermalManager.manage_heater();
		//	thermalManager.print_heaterstates();
			thermalManager.print_heater_states(e
#if ENABLED(TEMP_SENSOR_1_AS_REDUNDANT)
			, parser.boolval('R')
#endif
			);
	  
			SERIAL_EOL();
			time_s_old=time_s;
		}
		   
		if(tmpe_k=='\n'||tmpe_k=='\r')
		{

			//	printf(cmd_buf);
			if(cn>10)
			{
				if(cmd_buf[cn-2]=='h'&&(cmd_buf[0]=='A'||cmd_buf[0]=='U'||cmd_buf[cn-3]=='h'||tmpe_k=='\r'))
				{
					 SERIAL_ECHOPGM(cmd_buf);
					 SERIAL_EOL();
					  printf("tmpe_k===h\n");
					 cn=0;
					 
					 break;
				}
			}
			memset(cmd_buf,0,sizeof(cmd_buf));
			cn=0;
		}
		  // if(cmd_buf[cn-2])
		if(cn>60)
			cn=0;
			  

		usleep(1);

	}
   printf(cmd_buf);cn=0;
   
  
	
  ///////////////////
#endif
 // thermalManager.PID_autotune(temp, e, c, u);
  ui.reset_status();
}

#endif // HAS_PID_HEATING

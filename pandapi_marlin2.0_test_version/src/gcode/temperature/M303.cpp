/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "../../inc/MarlinConfig.h"

#if HAS_PID_HEATING

#include "../gcode.h"
#include "../../module/temperature.h"

/**
 * M303: PID relay autotune
 *
 *       S<temperature> sets the target temperature. (default 150C / 70C)
 *       E<extruder> (-1 for the bed) (default 0)
 *       C<cycles> Minimum 3. Default 5.
 *       U<bool> with a non-zero value will apply the result to current settings
 */
void GcodeSuite::M303() {
  #if ENABLED(PIDTEMPBED)
    #define SI H_BED
  #else
    #define SI H_E0
  #endif
  #if ENABLED(PIDTEMP)
    #define EI HOTENDS - 1
  #else
    #define EI H_BED
  #endif
  const heater_ind_t e = (heater_ind_t)parser.intval('E');
  if (!WITHIN(e, SI, EI)) {
    SERIAL_ECHOLNPGM(MSG_PID_BAD_EXTRUDER_NUM);
    return;
  }

  const int c = parser.intval('C', 5);
  const bool u = parser.boolval('U');
  const int16_t temp = parser.celsiusval('S', e < 0 ? 70 : 150);

  #if DISABLED(BUSY_WHILE_HEATING)
    KEEPALIVE_STATE(NOT_BUSY);
  #endif
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

 // thermalManager.PID_autotune(temp, e, c, u);
}

#endif // HAS_PID_HEATING

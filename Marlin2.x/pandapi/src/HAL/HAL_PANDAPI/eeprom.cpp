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
#ifdef PANDAPI// __AVR__

#include "../../inc/MarlinConfig.h"

#if EITHER(EEPROM_SETTINGS, SD_FIRMWARE_UPDATE)


#include <stdio.h>
#define E2END 0x2FFF // 12KB

FILE *fd_e2;

//int eeprom_index = EEPROM_OFFSET;
uint8_t e2p_cache[1024*20];

#include "../shared/eeprom_api.h"

#ifndef MARLIN_EEPROM_SIZE
  #define MARLIN_EEPROM_SIZE size_t(E2END + 1)
#endif
size_t PersistentStore::capacity()    { return MARLIN_EEPROM_SIZE; }
bool PersistentStore::access_start()  { return true; }
bool PersistentStore::access_finish() { return true; }
 
bool PersistentStore::write_data(int &pos, const uint8_t *value, size_t size, uint16_t *crc) {
  while (size--) {
    uint8_t * const p = (uint8_t * const)pos;
    uint8_t v = *value;
    // EEPROM has only ~100,000 write cycles,
    // so only write bytes that have changed!
    /*
    if (v != eeprom_read_byte(p)) {
      eeprom_write_byte(p, v);
      if (eeprom_read_byte(p) != v) {
        SERIAL_ECHO_MSG(MSG_ERR_EEPROM_WRITE);
        return true;
      }
    }*/// mark
    e2p_cache[pos]=v;
    
    crc16(crc, &v, 1);
    pos++;
    value++;
  };
  return false;
}



  void PersistentStore:: load_to_cache()
  {
	if((fd_e2=fopen("/home/pi/e2prom","rb"))==NULL)  
	{
	  SERIAL_ECHO_MSG("open e2prom failed!");
	  return ;
	}
	  
	// fseek(fd_e2,EEPROM_OFFSET,SEEK_SET);
			
	unsigned int n = fread(e2p_cache,sizeof(char),sizeof(e2p_cache),fd_e2);

	fclose(fd_e2);
//	for(int i=0;i<700;i++)
//		printf("0x%x,",e2p_cache[i]);
	
    printf("\nload_to_cache()===\n");

  }

void  PersistentStore::write_from_cache()
{
  if((fd_e2=fopen("/home/pi/e2prom","wb"))==NULL)	
  {
	SERIAL_ECHO_MSG("open e2prom failed!");
	return ;
  }
	
  // fseek(fd_e2,EEPROM_OFFSET,SEEK_SET);
  fwrite(e2p_cache,sizeof(char),sizeof(e2p_cache),fd_e2);	  
  //unsigned int n = fread(&sd_char,sizeof(char),sizeof(e2p_cache),fd_e2);

  fclose(fd_e2);
  //for(int i=0;i<700;i++)
  //	  printf("0x%x,",e2p_cache[i]);
	  
	

  printf("\nwrite_from_cache()===\n");
}

bool PersistentStore::read_data(int &pos, uint8_t* value, size_t size, uint16_t *crc, const bool writing/*=true*/) {
  do {
  //mark  uint8_t c = eeprom_read_byte((uint8_t*)pos);
    uint8_t c = e2p_cache[pos];
    if (writing) *value = c;
    crc16(crc, &c, 1);
    pos++;
    value++;
  } while (--size);
  return false;  // always assume success for AVR's
}



//size_t PersistentStore::capacity() { return E2END + 1; }

#endif // EEPROM_SETTINGS || SD_FIRMWARE_UPDATE
#endif // __AVR__

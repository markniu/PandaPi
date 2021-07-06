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

#include "../../../../../inc/MarlinConfigPre.h"

#if ENABLED(DGUS_LCD_UI_PANDAPI)
//PANDAPI
#include <stdio.h>

#include "../DGUSScreenHandler.h"

#include "../../../../../MarlinCore.h"
#include "../../../../../gcode/queue.h"
#include "../../../../../libs/duration_t.h"
#include "../../../../../module/settings.h"
#include "../../../../../module/temperature.h"
#include "../../../../../module/motion.h"
#include "../../../../../module/planner.h"
#include "../../../../../module/printcounter.h"
#include "../../../../../sd/cardreader.h"

#if ENABLED(POWER_LOSS_RECOVERY)
  #include "../../../../../feature/powerloss.h"
#endif


extern uint16_t octopi_choose_status;
extern int octopi_file_num;
extern char print_filename[128];
extern ExtUI::FileList filelist;
extern char buffer[1024*10]; 
extern char parse_string(char *src,char *start,char *end,char *out,int *e_pos);

#if ENABLED(SDSUPPORT)

  void DGUSScreenHandler::DGUSLCD_SD_FileSelected(DGUS_VP_Variable &var, void *val_ptr) {
    uint16_t touched_nr = (int16_t)swap16(*(uint16_t*)val_ptr) + top_file;
	//PANDAPI
	if(octopi_choose_status)
	{
		 int k=0,len=0,i=0;
		 char out_t[1024];
		 if (touched_nr >= octopi_file_num) return;
		 printf("touched_nr:%d/%d\n",touched_nr,octopi_file_num);
		 file_to_print = touched_nr;
		 for(i=0;i<=touched_nr;i++)
		 {
			 parse_string(buffer+len,"\"resource\":","}",out_t,&k);
			 len+=k;
			 parse_string(out_t,"http://localhost/api/files/","\"",print_filename,&k);
			 
			 if(len>=(sizeof(buffer)-10))
			 {
				 
				 memset(print_filename,0,sizeof(print_filename));
			 }
			 //printf("%s : %d\n",tmpfilename,i);
		 }

		#if ENABLED(DGUS_PRINT_FILENAME)
	      // Send print filename
	      dgusdisplay.WriteVariable(VP_SD_Print_Filename, print_filename, VP_SD_FileName_LEN, true);
	    #endif
		 HandleUserConfirmationPopUp(VP_SD_FileSelectConfirm, nullptr, PSTR("Print file"), print_filename, PSTR("from SD Card?"), true, true, false, true);
	}
	else
	{
	 
	    if (touched_nr > filelist.count()) return;
	    if (!filelist.seek(touched_nr)) return;
	    if (filelist.isDir()) {
	      filelist.changeDir(filelist.filename());
	      top_file = 0;
	      ForceCompleteUpdate();
	      return;
	    }

    #if ENABLED(DGUS_PRINT_FILENAME)
      // Send print filename
      dgusdisplay.WriteVariable(VP_SD_Print_Filename, filelist.filename(), VP_SD_FileName_LEN, true);
    #endif

    // Setup Confirmation screen
    file_to_print = touched_nr;

    HandleUserConfirmationPopUp(VP_SD_FileSelectConfirm, nullptr, PSTR("Print file"), filelist.filename(), PSTR("from SD Card?"), true, true, false, true);
	}
  }

  void DGUSScreenHandler::DGUSLCD_SD_StartPrint(DGUS_VP_Variable &var, void *val_ptr) {
//PANDAPI
	if(octopi_choose_status)
	{

		 char tmpdata[256];
		 sprintf(tmpdata,"curl -s     -X POST -H \"Content-Type: application/json\" -d	\"{\\\"command\\\":\\\"select\\\",\\\"print\\\":true}\" http://localhost/api/files/%s	 ",print_filename);
	//	printf("\ntmpdata====%s\n",tmpdata);
		//pf = popen(tmpdata, "r");
	  //  fread(buffer, sizeof(buffer), 1, pf);
	 //   printf("%s\n", buffer);   
	  //  pclose(pf);
	  send_to_curl(tmpdata);
	}	
	else
	{
	    if (!filelist.seek(file_to_print)) return;
	    ExtUI::printFile(filelist.shortFilename());
	}
	 GotoScreen(
  #if ENABLED(DGUS_LCD_UI_ORIGIN)
		DGUSLCD_SCREEN_STATUS
  #else
		DGUSLCD_SCREEN_SDPRINTMANIPULATION
  #endif
	);
    
  }

  void DGUSScreenHandler::DGUSLCD_SD_ResumePauseAbort(DGUS_VP_Variable &var, void *val_ptr) {
  //PANDAPI
 //   if (!ExtUI::isPrintingFromMedia()) return; // avoid race condition when user stays in this menu and printer finishes.
    switch (swap16(*(uint16_t*)val_ptr)) {
      case 0: { // Resume
	        //  
		if(octopi_choose_status)	
		{
		  //pf = popen("curl -s     -X POST -H \"Content-Type: application/json\" -d  \"{\\\"command\\\":\\\"pause\\\",\\\"action\\\":\\\"resume\\\"}\" http://localhost/api/job  -H @/boot/octopi_key.txt", "r");
		  //fread(buffer, sizeof(buffer), 1, pf);
		  //printf("%s\n", buffer);	
		  //pclose(pf); 
		  send_to_curl("curl -s     -X POST -H \"Content-Type: application/json\" -d  \"{\\\"command\\\":\\\"pause\\\",\\\"action\\\":\\\"resume\\\"}\" http://localhost/api/job  ");
		}
		
        if (ExtUI::isPrintingFromMediaPaused()) {
          ExtUI::resumePrint();
        }
      } break;

      case 1: // Pause

        //GotoScreen(MKSLCD_SCREEN_PAUSE);
       // 
		if(octopi_choose_status)
		{
		//	pf = popen("curl -s     -X POST -H \"Content-Type: application/json\" -d  \"{\\\"command\\\":\\\"pause\\\",\\\"action\\\":\\\"pause\\\"}\" http://localhost/api/job -H @/boot/octopi_key.txt", "r");
		//	fread(buffer, sizeof(buffer), 1, pf);
		//	printf("%s\n", buffer);	 
		//	pclose(pf); 
			send_to_curl("curl -s     -X POST -H \"Content-Type: application/json\" -d  \"{\\\"command\\\":\\\"pause\\\",\\\"action\\\":\\\"pause\\\"}\" http://localhost/api/job");
		}
		
		
        if (!ExtUI::isPrintingFromMediaPaused()) {
          ExtUI::pausePrint();
          //ExtUI::mks_pausePrint();
        }
        break;
      case 2: // Abort
        HandleUserConfirmationPopUp(VP_SD_AbortPrintConfirmed, nullptr, PSTR("Abort printing"), filelist.filename(), PSTR("?"), true, true, false, true);
        break;
    }
  }

  void DGUSScreenHandler::DGUSLCD_SD_SendFilename(DGUS_VP_Variable& var) {
    uint16_t target_line = (var.VP - VP_SD_FileName0) / VP_SD_FileName_LEN;
    if (target_line > DGUS_SD_FILESPERSCREEN) return;
    char tmpfilename[VP_SD_FileName_LEN + 1] = "";
    var.memadr = (void*)tmpfilename;
	//PANDAPI
	if(octopi_choose_status)
	{
		int k=0,len=0,i=0;
		char out_t[1024];
	   // pf = popen("curl -s   http://localhost//api/files?recursive=true -H @/boot/octopi_key.txt", "r");
	   // fread(buffer, sizeof(buffer), 1, pf);
	    // printf("%s\n", buffer);   
	   // pclose(pf);	
	    send_to_curl("curl -s   http://localhost//api/files?recursive=true");
	    while(i<100)
	    {
	    	parse_string(buffer+len,"\"resource\":","}",out_t,&k);
			len+=k;
			if(parse_string(out_t,"http://localhost/api/files/","\"",tmpfilename,&k)==1)
				break;
			len+=k;
			i++; 
				
			 
		}
		octopi_file_num=i++;// total files
		//printf("===%d/%d\n",target_line,octopi_file_num); 
		k=len=0;
		for(i=0;i<=top_file+target_line;i++)
		{
			parse_string(buffer+len,"\"resource\":","}",out_t,&k);
			len+=k;
			parse_string(out_t,"http://localhost/api/files/","\"",tmpfilename,&k);
			len+=k;
		 	if(len>=(sizeof(buffer)-10))
		 	{
		 		
				memset(tmpfilename,0,sizeof(tmpfilename));
		 	}
		//	 printf("%s : %d\n",tmpfilename,i);
		}
	}
	else if (filelist.seek(top_file + target_line)) {
      snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s%c"), filelist.filename(), filelist.isDir() ? '/' : 0); // snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s"), filelist.filename());
    }
    DGUSLCD_SendStringToDisplay(var);
  }

  void DGUSScreenHandler::SDCardInserted() {
    top_file = 0;
    filelist.refresh();
    auto cs = getCurrentScreen();
    if (cs == DGUSLCD_SCREEN_MAIN || cs == DGUSLCD_SCREEN_STATUS)
      GotoScreen(DGUSLCD_SCREEN_SDFILELIST);
  }

  void DGUSScreenHandler::SDCardRemoved() {
    if (current_screen == DGUSLCD_SCREEN_SDFILELIST
        || (current_screen == DGUSLCD_SCREEN_CONFIRM && (ConfirmVP == VP_SD_AbortPrintConfirmed || ConfirmVP == VP_SD_FileSelectConfirm))
        || current_screen == DGUSLCD_SCREEN_SDPRINTMANIPULATION
    ) GotoScreen(DGUSLCD_SCREEN_MAIN);
  }

#endif // SDSUPPORT

void DGUSScreenHandler::ScreenChangeHook(DGUS_VP_Variable &var, void *val_ptr) {
  uint8_t *tmp = (uint8_t*)val_ptr;

  // The keycode in target is coded as <from-frame><to-frame>, so 0x0100A means
  // from screen 1 (main) to 10 (temperature). DGUSLCD_SCREEN_POPUP is special,
  // meaning "return to previous screen"
  DGUSLCD_Screens target = (DGUSLCD_Screens)tmp[1];

  DEBUG_ECHOLNPAIR("\n DEBUG target", target);

  if (target == DGUSLCD_SCREEN_POPUP) {
    // Special handling for popup is to return to previous menu
    if (current_screen == DGUSLCD_SCREEN_POPUP && confirm_action_cb) confirm_action_cb();
    PopToOldScreen();
    return;
  }

  UpdateNewScreen(target);

  #ifdef DEBUG_DGUSLCD
    if (!DGUSLCD_FindScreenVPMapList(target)) DEBUG_ECHOLNPAIR("WARNING: No screen Mapping found for ", target);
  #endif
}

void DGUSScreenHandler::HandleManualMove(DGUS_VP_Variable &var, void *val_ptr) {
  DEBUG_ECHOLNPGM("HandleManualMove");

  int16_t movevalue = swap16(*(uint16_t*)val_ptr);
  #if DISABLED(DGUS_UI_MOVE_DIS_OPTION)
    if (movevalue) {
      const uint16_t choice = *(uint16_t*)var.memadr;
      movevalue = movevalue < 0 ? -choice : choice;
    }
  #endif
  char axiscode;
  unsigned int speed = 1500; // FIXME: get default feedrate for manual moves, dont hardcode.

  switch (var.VP) {
    default: return;

    case VP_MOVE_X:
      axiscode = 'X';
      if (!ExtUI::canMove(ExtUI::axis_t::X)) goto cannotmove;
      break;

    case VP_MOVE_Y:
      axiscode = 'Y';
      if (!ExtUI::canMove(ExtUI::axis_t::Y)) goto cannotmove;
      break;

    case VP_MOVE_Z:
      axiscode = 'Z';
      speed = 300; // default to 5mm/s
      if (!ExtUI::canMove(ExtUI::axis_t::Z)) goto cannotmove;
      break;

    case VP_HOME_ALL: // only used for homing
      axiscode  = '\0';
      movevalue = 0; // ignore value sent from display, this VP is _ONLY_ for homing.
      break;
  }

  if (!movevalue) {
    // homing
    DEBUG_ECHOPAIR(" homing ", AS_CHAR(axiscode));
    char buf[6] = "G28 X";
    buf[4] = axiscode;
    //DEBUG_ECHOPAIR(" ", buf);
    queue.enqueue_one_now(buf);
    //DEBUG_ECHOLNPGM(" ✓");
    ForceCompleteUpdate();
    return;
  }
  else {
    // movement
    DEBUG_ECHOPAIR(" move ", AS_CHAR(axiscode));
    bool old_relative_mode = relative_mode;
    if (!relative_mode) {
      //DEBUG_ECHOPGM(" G91");
      queue.enqueue_now_P(PSTR("G91"));
      //DEBUG_ECHOPGM(" ✓ ");
    }
    char buf[32]; // G1 X9999.99 F12345
    unsigned int backup_speed = MMS_TO_MMM(feedrate_mm_s);
    char sign[] = "\0";
    int16_t value = movevalue / 100;
    if (movevalue < 0) { value = -value; sign[0] = '-'; }
    int16_t fraction = ABS(movevalue) % 100;
    snprintf_P(buf, 32, PSTR("G0 %c%s%d.%02d F%d"), axiscode, sign, value, fraction, speed);
    //DEBUG_ECHOPAIR(" ", buf);
    queue.enqueue_one_now(buf);
    //DEBUG_ECHOLNPGM(" ✓ ");
    if (backup_speed != speed) {
      snprintf_P(buf, 32, PSTR("G0 F%d"), backup_speed);
      queue.enqueue_one_now(buf);
      //DEBUG_ECHOPAIR(" ", buf);
    }
    // while (!enqueue_and_echo_command(buf)) idle();
    //DEBUG_ECHOLNPGM(" ✓ ");
    if (!old_relative_mode) {
      //DEBUG_ECHOPGM("G90");
      queue.enqueue_now_P(PSTR("G90"));
      //DEBUG_ECHOPGM(" ✓ ");
    }
  }

  ForceCompleteUpdate();
  DEBUG_ECHOLNPGM("manmv done.");
  return;

  cannotmove:
    DEBUG_ECHOLNPAIR(" cannot move ", AS_CHAR(axiscode));
    return;
}

#if HAS_PID_HEATING
  void DGUSScreenHandler::HandleTemperaturePIDChanged(DGUS_VP_Variable &var, void *val_ptr) {
    uint16_t rawvalue = swap16(*(uint16_t*)val_ptr);
    DEBUG_ECHOLNPAIR("V1:", rawvalue);
    float value = (float)rawvalue / 10;
    DEBUG_ECHOLNPAIR("V2:", value);
    float newvalue = 0;

    switch (var.VP) {
      default: return;
        #if HOTENDS >= 1
          case VP_E0_PID_P: newvalue = value; break;
          case VP_E0_PID_I: newvalue = scalePID_i(value); break;
          case VP_E0_PID_D: newvalue = scalePID_d(value); break;
        #endif
        #if HOTENDS >= 2
          case VP_E1_PID_P: newvalue = value; break;
          case VP_E1_PID_I: newvalue = scalePID_i(value); break;
          case VP_E1_PID_D: newvalue = scalePID_d(value); break;
        #endif
        #if HAS_HEATED_BED
          case VP_BED_PID_P: newvalue = value; break;
          case VP_BED_PID_I: newvalue = scalePID_i(value); break;
          case VP_BED_PID_D: newvalue = scalePID_d(value); break;
        #endif
    }

    DEBUG_ECHOLNPAIR_F("V3:", newvalue);
    *(float *)var.memadr = newvalue;

    skipVP = var.VP; // don't overwrite value the next update time as the display might autoincrement in parallel
  }
#endif // HAS_PID_HEATING

#if ENABLED(BABYSTEPPING)
  void DGUSScreenHandler::HandleLiveAdjustZ(DGUS_VP_Variable &var, void *val_ptr) {
    DEBUG_ECHOLNPGM("HandleLiveAdjustZ");
    int16_t flag  = swap16(*(uint16_t*)val_ptr),
            steps = flag ? -20 : 20;
    ExtUI::smartAdjustAxis_steps(steps, ExtUI::axis_t::Z, true);
    ForceCompleteUpdate();
  }
#endif

#if ENABLED(DGUS_FILAMENT_LOADUNLOAD)

  void DGUSScreenHandler::HandleFilamentOption(DGUS_VP_Variable &var, void *val_ptr) {
    DEBUG_ECHOLNPGM("HandleFilamentOption");

    uint8_t e_temp = 0;
    filament_data.heated = false;
    uint16_t preheat_option = swap16(*(uint16_t*)val_ptr);
    if (preheat_option <= 8) {      // Load filament type
      filament_data.action = 1;
    }
    else if (preheat_option >= 10) { // Unload filament type
      preheat_option -= 10;
      filament_data.action = 2;
      filament_data.purge_length = DGUS_FILAMENT_PURGE_LENGTH;
    }
    else {                          // Cancel filament operation
      filament_data.action = 0;
    }

    switch (preheat_option) {
      case 0: // Load PLA
        #ifdef PREHEAT_1_TEMP_HOTEND
          e_temp = PREHEAT_1_TEMP_HOTEND;
        #endif
        break;
      case 1: // Load ABS
        TERN_(PREHEAT_2_TEMP_HOTEND, e_temp = PREHEAT_2_TEMP_HOTEND);
        break;
      case 2: // Load PET
        #ifdef PREHEAT_3_TEMP_HOTEND
          e_temp = PREHEAT_3_TEMP_HOTEND;
        #endif
        break;
      case 3: // Load FLEX
        #ifdef PREHEAT_4_TEMP_HOTEND
          e_temp = PREHEAT_4_TEMP_HOTEND;
        #endif
        break;
      case 9: // Cool down
      default:
        e_temp = 0;
        break;
    }

    if (filament_data.action == 0) { // Go back to utility screen
      #if HOTENDS >= 1
        thermalManager.setTargetHotend(e_temp, ExtUI::extruder_t::E0);
      #endif
      #if HOTENDS >= 2
        thermalManager.setTargetHotend(e_temp, ExtUI::extruder_t::E1);
      #endif
      GotoScreen(DGUSLCD_SCREEN_UTILITY);
    }
    else { // Go to the preheat screen to show the heating progress
      switch (var.VP) {
        default: return;
          #if HOTENDS >= 1
            case VP_E0_FILAMENT_LOAD_UNLOAD:
              filament_data.extruder = ExtUI::extruder_t::E0;
              thermalManager.setTargetHotend(e_temp, filament_data.extruder);
              break;
          #endif
          #if HOTENDS >= 2
            case VP_E1_FILAMENT_LOAD_UNLOAD:
              filament_data.extruder = ExtUI::extruder_t::E1;
              thermalManager.setTargetHotend(e_temp, filament_data.extruder);
              break;
          #endif
      }
      GotoScreen(DGUSLCD_SCREEN_FILAMENT_HEATING);
    }
  }

  void DGUSScreenHandler::HandleFilamentLoadUnload(DGUS_VP_Variable &var) {
    DEBUG_ECHOLNPGM("HandleFilamentLoadUnload");
    if (filament_data.action <= 0) return;

    // If we close to the target temperature, we can start load or unload the filament
    if (thermalManager.hotEnoughToExtrude(filament_data.extruder) && \
        thermalManager.targetHotEnoughToExtrude(filament_data.extruder)) {
      float movevalue = DGUS_FILAMENT_LOAD_LENGTH_PER_TIME;

      if (filament_data.action == 1) { // load filament
        if (!filament_data.heated) {
          //GotoScreen(DGUSLCD_SCREEN_FILAMENT_LOADING);
          filament_data.heated = true;
        }
        movevalue = ExtUI::getAxisPosition_mm(filament_data.extruder) + movevalue;
      }
      else { // unload filament
        if (!filament_data.heated) {
          GotoScreen(DGUSLCD_SCREEN_FILAMENT_UNLOADING);
          filament_data.heated = true;
        }
        // Before unloading extrude to prevent jamming
        if (filament_data.purge_length >= 0) {
          movevalue = ExtUI::getAxisPosition_mm(filament_data.extruder) + movevalue;
          filament_data.purge_length -= movevalue;
        }
        else {
          movevalue = ExtUI::getAxisPosition_mm(filament_data.extruder) - movevalue;
        }
      }
      ExtUI::setAxisPosition_mm(movevalue, filament_data.extruder);
    }
  }
#endif // DGUS_FILAMENT_LOADUNLOAD

bool DGUSScreenHandler::loop() {
  dgusdisplay.loop();

  const millis_t ms = millis();
  static millis_t next_event_ms = 0;
  //PANDAPI
  static millis_t next_octopi_ms = 0;
  static uint16_t octopi_choose_status_old=0;

  if (!IsScreenComplete() || ELAPSED(ms, next_event_ms)) {
    next_event_ms = ms + DGUS_UPDATE_INTERVAL_MS;
    UpdateScreenVPData();
	//PANDAPI
	if((current_screen==DGUSLCD_SCREEN_INFOS||current_screen==DGUSLCD_SCREEN_MAIN)&&ELAPSED(ms, next_octopi_ms))
	{
	  int k=0;
	  char out_t[128],out_2[128];;
	  next_octopi_ms=ms+DGUS_UPDATE_INTERVAL_MS*2;
	 // pf = popen("curl -s   http://localhost/api/job -H @/boot/octopi_key.txt", "r");
	 // fread(buffer, sizeof(buffer), 1, pf);
	//	printf("%s\n", buffer); 
	 // pclose(pf); 
      send_to_curl("curl -s   http://localhost/api/job");
	  parse_string(buffer,"\"state\":","}",out_t,&k);

	  if(parse_string(out_t,"Operational","\"",out_2,&k)!=1)
		  octopi_choose_status=1;
	  else if(parse_string(out_t,"Printing","\"",out_2,&k)!=1)
	  	  octopi_choose_status=2;
	  else if(parse_string(out_t,"Paused","\"",out_2,&k)!=1)
	  	  octopi_choose_status=3;
/*
	  if(strncmp(out_t,"Operational",sizeof("Operational"))==0)
		  octopi_choose_status=1;
	  else if(strncmp(out_t,"Printing",sizeof("Printing"))==0)
	  	  octopi_choose_status=2;
	  else if(strncmp(out_t,"Paused",sizeof("Paused"))==0)
	  	  octopi_choose_status=3;
	  */
	  else
	  	  octopi_choose_status=0;
//printf("out_t:%s octopi_choose_status:%d\n",out_t,octopi_choose_status);
	if(octopi_choose_status_old!=octopi_choose_status) 
	  {
	  	octopi_choose_status_old=octopi_choose_status;
		if(octopi_choose_status==2)
			GotoScreen(DGUSLCD_SCREEN_SDPRINTMANIPULATION);
	  }
	  
			  
		//  return GotoScreen(DGUSLCD_SCREEN_SDPRINTMANIPULATION);
	}
  }

  #if ENABLED(SHOW_BOOTSCREEN)
    static bool booted = false;

    if (!booted && TERN0(POWER_LOSS_RECOVERY, recovery.valid()))
      booted = true;

    if (!booted && ELAPSED(ms, TERN(USE_MKS_GREEN_UI, 1000, BOOTSCREEN_TIMEOUT))){
		GotoScreen(DGUSLCD_SCREEN_MAIN);// PANDAPI
        booted = true;
    }
  #endif
  return IsScreenComplete();
}

#endif // DGUS_LCD_UI_FYSETC

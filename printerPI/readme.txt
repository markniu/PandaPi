/**
  @page LTDC_ColorKeying  LTDC Color Keying example

  @verbatim
  ******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
  * @file    LTDC_ColorKeying/readme.txt 
  * @version V1.0.1
  * @date    11-November-2013
  * @brief   Description of the LTDC Color Keying Example
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  @endverbatim

@par Example Description 

 This example describes how to enable and use the color keying functionality.
 
 After LCD initialization, LCD layer 1 and color keying configuration, an image 
 is displayed on LCD. The image is formed by six arrows each with a different 
 color.
 
 Color keying is enabled/disabled on the image when the user button is pressed.
 In this example, six color keys are configured. Each time the user button is 
 pressed, a color key is set and the correspendant arrow's pixels are set to 
 0xFF (black).
       
 Color Keying :
 --------------
 If the Color Keying is enabled, all pixels are compared to the color key. 
 If they match the programmed RGB value, all channels (ARGB) of that pixel 
 are set to 0xFF.


@par Directory contents 

  - LTDC_ColorKeying/system_stm32f4xx.c   STM32F4xx system clock configuration file
  - LTDC_ColorKeying/stm32f4xx_conf.h     Library Configuration file
  - LTDC_ColorKeying/stm32f4xx_it.h       Interrupt handlers header file
  - LTDC_ColorKeying/stm32f4xx_it.c       Interrupt handlers
  - LTDC_ColorKeying/main.c               Main program
  - LTDC_ColorKeying/main.h               Main program header file


@par Hardware and Software environment 

  - This example runs on STM32F429x Devices RevY.
  
  - This example has been tested with STM32F429I-DISCO (MB1075) RevB and can be
    easily tailored to any other development board.

@par How to use it ? 

In order to make the program work, you must do the following :

  + EWARM
    - Open the LTDC_ColorKeying.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)
  
 + MDK-ARM
    - Open the LTDC_ColorKeying.uvproj project
    - Rebuild all files: Project->Rebuild all target files
    - Load project image: Debug->Start/Stop Debug Session
    - Run program: Debug->Run (F5)  
    
 + TrueSTUDO
    - Open the TrueSTUDIO toolchain.
    - Click on File->Switch Workspace->Other and browse to TrueSTUDIO workspace directory.
    - Click on File->Import, select General->'Existing Projects into Workspace' and then click "Next". 
    - Browse to the TrueSTUDIO workspace directory, select the project.
    - Rebuild all project files: Select the project in the "Project explorer" 
      window then click on Project->build project menu.
    - Run program: Run->Debug (F11)  
    
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

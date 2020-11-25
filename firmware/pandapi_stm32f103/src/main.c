
// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>


#include "stm32f10x.h"
#include "Timer.h"
#include "stm32f10x_iwdg.h"
#define BLINK_ON_TICKS  (TIMER_FREQUENCY_HZ * 3 / 4)
#define BLINK_OFF_TICKS (TIMER_FREQUENCY_HZ - BLINK_ON_TICKS)
extern float gt[5];
extern   extruder_status   Extruder;
extern bed_status Bed_tmper;

  typedef struct { float Kp, Ki, Kd;	 } PID_t;
  typedef struct { float Kp, Ki, Kd, Kc; } PIDC_t;
  typedef struct { float Kp, Ki, Kd, Kf; } PIDF_t;
  typedef struct { float Kp, Ki, Kd, Kc, Kf; } PIDCF_t;
#define true 1
#define false 0
extern  unsigned char  soft_pwm_amount[2],auto_tune;
_Bool wait_for_heatup=0;
  // PID storage
  unsigned long ms_count_n=0;

  #define false 0
  #define true 1
  unsigned long millis(void)
   {
   	return ms_count_n;

   }
// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_InitStructure.NVIC_IRQChannel = I2C2_EV_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}

void I2C2_ClearFlag(void) {
  // ADDR-Flag clear
  while((I2C2->SR1 & I2C_SR1_ADDR) == I2C_SR1_ADDR) {
    I2C2->SR1;
    I2C2->SR2;
  }

  // STOPF Flag clear
  while((I2C2->SR1&I2C_SR1_STOPF) == I2C_SR1_STOPF) {
    I2C2->SR1;
    I2C2->CR1 |= 0x1;
  }
}
void IIC_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  I2C_InitTypeDef I2C_InitStructure;

  RCC_APB2PeriphClockCmd  (RCC_APB2Periph_GPIOB , ENABLE);


   /* Configure I2C2 pins: SCL and SDA */
   GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_10|GPIO_Pin_11; //10:SCL 11:SDA
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_OD;//Out_PP;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
       /* Enable I2C1 reset state */
   RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, ENABLE);
       /* Release I2C1 from reset state */
   RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, DISABLE);

   I2C_DeInit(I2C2);
   I2C_InitStructure.I2C_Mode =I2C_Mode_SMBusDevice;// I2C_Mode_I2C;//I2C_Mode_SMBusDevice;
   I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
   I2C_InitStructure.I2C_OwnAddress1 = 0x3c<<1;//0x10<<1;//temp addr
   I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
   I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
   I2C_InitStructure.I2C_ClockSpeed = 40000;
   I2C_Init(I2C2, &I2C_InitStructure);


   I2C_Cmd(I2C2,ENABLE);
   I2C_ITConfig(I2C2, I2C_IT_EVT|I2C_IT_BUF, ENABLE);
}
void I2C2_ER_IRQHandler(void)

{

 /* Check on I2C1 AF flag and clear it */

 if (I2C_GetITStatus(I2C2, I2C_IT_AF))

 {

  /* 这个就是图243中最后那个没有应答的中断，也就是发送了一串数据后的中断，可以做清零工作 */

  I2C_ClearITPendingBit(I2C2, I2C_IT_AF);

  //Tx_Idx = 0;



 }

 /* Check on I2C1 AF flag and clear it */

 if (I2C_GetITStatus(I2C2, I2C_IT_BERR))   //这个就是起始和停止条件出错了

 {

  I2C_ClearITPendingBit(I2C2, I2C_IT_BERR);

  }

 }

#define MIN_PULSE_WIDTH       1000     // the shortest pulse sent to a servo

static void TIM_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

  // 输出比较通道互补通道 GPIO 初始化

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

}
void Servo_Timer_Config(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef	TIM_OCInitStructure;

	TIM_GPIO_Config();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //使能TIMx外设


	TIM_TimeBaseStructure.TIM_Period= 20000-1;//(200-1);
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= 72-1;//(72-1);
	// TIM_TimeBaseStructure.TIM_Period = arr; //设置自动重装载周期值
	// TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置预分频值 不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx

    TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;																  //CH2 PWM2模式
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;		//比较输出使能
	TIM_OCInitStructure.TIM_Pulse =MIN_PULSE_WIDTH;//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //OC2 低电平有效
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //根据指定的参数初始化外设TIMx


	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);	//CH4 预装载使能

  	TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器

	TIM_CtrlPWMOutputs(TIM1,ENABLE);		 //MOE 主输出使能,高级定时器必须开启这个

	TIM_Cmd(TIM1, ENABLE);  //使能TIMx

}



void write_pwm(int value)
{
	 TIM_SetCompare4(TIM1, value); //

}


#define max_rebuf  60
// receive form server data
typedef struct
{
	int receive_len;
	int receive_status; /*1  : idle,0:receiving,2,wait process*/
	char   receive_buf[max_rebuf];

} Receive_D;
Receive_D  Receive_CMD[2];
static uint8_t I2C_Buffer_Tx[128];//0:len  1...=>data
uint8_t I2C_Buffer_Tx_cache[128];

int  Tx_I2C_num=0;
void  PID_autotune( int target, int heater, unsigned char ncycles, _Bool set_result/*=false*/);

int  tune_e,tune_c,tune_u,tune_temp,tune_start=0;;

void I2C_TX_checksum(uint8_t *data_o)
{
	uint8_t checksum=0;
	int count = strlen(data_o);
	while (count) checksum ^= data_o[--count];
	sprintf(I2C_Buffer_Tx,"%s *%d\n\0",data_o,checksum);
}

void cmd_pase(char *data_c,int len)
{
 	int i;
 	int date;
	for(i=0;i<len;i++)
	{

		if(data_c[i]=='t')		   // extruder0 target temperature
		{
			date=atoi(data_c+i+1);
			Extruder.tar_temper[0]=date*10;
			if(Extruder.tar_temper[0]>3000)
				Extruder.tar_temper[0]=0;
			sprintf(I2C_Buffer_Tx_cache,"ok %d",date);
			I2C_TX_checksum(I2C_Buffer_Tx_cache);
			break;
		}
		if(data_c[i]=='T')		   // extruder1 target temperature
		{
			date=atoi(data_c+i+1);
			Extruder.tar_temper[1]=date*10;
			if(Extruder.tar_temper[1]>3000)
				Extruder.tar_temper[1]=0;
			sprintf(I2C_Buffer_Tx_cache,"ok %d",date);
			I2C_TX_checksum(I2C_Buffer_Tx_cache);
			break;
		}
		else if(data_c[i]=='P')		   //set pwm value
		{
			date=atoi(data_c+i+1);
			write_pwm(date);
			sprintf(I2C_Buffer_Tx_cache,"ok %d",date);
			I2C_TX_checksum(I2C_Buffer_Tx_cache);
			break;
		}
		else if(data_c[i]=='K')		   // PID: K value
		{
			Extruder.kp[0]=atof(data_c+i+1);
			sprintf(I2C_Buffer_Tx_cache,"ok %.1f",Extruder.kp);
			I2C_TX_checksum(I2C_Buffer_Tx_cache);
			break;
		}
		else if(data_c[i]=='I')		   // PID: I value
		{
			Extruder.ki[0]=atof(data_c+i+1);
			sprintf(I2C_Buffer_Tx_cache,"ok %.1f",Extruder.ki);
			I2C_TX_checksum(I2C_Buffer_Tx_cache);
			break;
		}
		else if(data_c[i]=='D')		   // PID: D value
		{
			Extruder.kd[0]=atof(data_c+i+1);
			sprintf(I2C_Buffer_Tx_cache,"ok %.1f",Extruder.kd);
			I2C_TX_checksum(I2C_Buffer_Tx_cache);
			break;
		}
		else if(data_c[i]=='F')		   // fans speed 0~10
		{
			int nui=data_c[i+1]-'0';
			date=atoi(data_c+i+1+2);
			if(nui==0)
				Extruder.fan0[0]=date;
			else if(nui==1)
				Extruder.fan1[0]=date;
			else if(nui==3)
				Extruder.fan3[0]=date;
			else
				Extruder.fan2[0]=date; //board fan
			sprintf(I2C_Buffer_Tx_cache,"ok %d",date);
			I2C_TX_checksum(I2C_Buffer_Tx_cache);
			break;
		}
		else if(data_c[i]=='b')		   // bed target temperature
		{
			date=atoi(data_c+i+1);
			Bed_tmper.tar_temper=date*10;
			if(Bed_tmper.tar_temper>3000)
				Bed_tmper.tar_temper=0;
			sprintf(I2C_Buffer_Tx_cache,"ok %d",date);
			I2C_TX_checksum(I2C_Buffer_Tx_cache);
			//Extruder.fan1=atoi(data_c+i+1);
			//if(Extruder.fan1==0)
				//fan1_pin=0;
			break;
		}
		else if(data_c[i]=='g')		   // get temperature
		{
			//static int pin14_v=-1;
			int out=(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_14)<<1)|GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13);
		  	unsigned char u=atoi(data_c+i+1);
		  	if(u>=4)
		  		break;
		//	if(pin14_v!=out)
			//{
			//	pin14_v=out;
				sprintf(I2C_Buffer_Tx_cache,"h%dT:%d.%dB:%d.%dT1:%d.%d",out,Extruder.rel_temper[0]/10,Extruder.rel_temper[0]%10,
					Bed_tmper.rel_temper/10,Bed_tmper.rel_temper%10,
					Extruder.rel_temper[1]/10,Extruder.rel_temper[1]%10);
		        I2C_TX_checksum(I2C_Buffer_Tx_cache);
			//}
			//else
			//	sprintf(I2C_Buffer_Tx,"T:%d.%dB:%d.%d\n",Extruder.rel_temper/10,Extruder.rel_temper%10,
			//		Bed_tmper.rel_temper/10,Bed_tmper.rel_temper%10);
				

			break;
		}
		else if(data_c[i]=='G')		   // get temperature
		{

		  	unsigned char u=atoi(data_c+i+1);
		  	if(u>=4)
		  		break;
			//TMP102_Temperature_Write(0x0d,u);
			//TMP102_Temperature_Write(0x0e,u);
			sprintf(I2C_Buffer_Tx_cache,"T:%d.%d C",Bed_tmper.rel_temper/10,Bed_tmper.rel_temper%10);
			I2C_TX_checksum(I2C_Buffer_Tx_cache);

			break;
		}
		else if(data_c[i]=='h')		   // filament sensor
		{
			int out=(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_14)<<1)|GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13);
			sprintf(I2C_Buffer_Tx_cache,"h%d",out);
			I2C_TX_checksum(I2C_Buffer_Tx_cache);
			break;
		}
		else if(data_c[i]=='w')		   // get firmware version
		{
			//  (" ReD:V1.1.5,compile date:" __DATE__ " " __TIME__"\r\n" )
			sprintf(I2C_Buffer_Tx,"V1 " __DATE__ "\n");
			break;
		}
		else if(data_c[i]=='r')		   // reboot
		{
			//  (" ReD:V1.1.5,compile date:" __DATE__ " " __TIME__"\r\n" )
			__set_FAULTMASK(1);//
			NVIC_SystemReset();//
			break;
		}
		else if(data_c[i]=='a')		   // get firmware version
		{
			//  (" ReD:V1.1.5,compile date:" __DATE__ " " __TIME__"\r\n" )
			char out[64];
			int k=0;
			Extruder.ki[0]=atoi(data_c+i+1);

			parse_string(data_c+i+1,"E",",",out,&k);
			tune_e= atoi(out);
			if(tune_e>1||tune_e<0)
			{
				sprintf(I2C_Buffer_Tx,"E number >1 !\n");
				break;
			}
			parse_string(data_c+i+1,"C",",",out,&k);
			tune_c= atoi(out);
			parse_string(data_c+i+1,"U",",",out,&k);
			tune_u= atoi(out);
			parse_string(data_c+i+1,"S",";",out,&k);	
			tune_temp= atoi(out);
			if(tune_temp>50&&tune_temp<300)
            	tune_start=1;
		//	int c = parser.intval('C', 5);
		//	_Bool u = parser.boolval('U');
		//	int temp = parser.celsiusval('S', e < 0 ? 70 : 150);
		 	sprintf(I2C_Buffer_Tx,"ok\n");
			

			break;
		}
		
		else if(data_c[i]=='M')		   // reboot
		{
			//gcode_M108() 
			unsigned char u=atoi(data_c+i+1);
			if(u==108)
				wait_for_heatup = false;  
			sprintf(I2C_Buffer_Tx,"ok\n");
			break;
		}
		
	}

}

void receing_data(char datar)
{

	if(datar==';')
	{
		Receive_CMD[0].receive_buf[Receive_CMD[0].receive_len++] = 0;
		Receive_CMD[0].receive_status=2;
		/////
		char *apos = strrchr(Receive_CMD[0].receive_buf, '*');
		if (apos) // has checksum
		{
		  uint8_t checksum = 0, count =  (apos - Receive_CMD[0].receive_buf);
		  while (count) checksum ^= Receive_CMD[0].receive_buf[--count];
		  if (strtol(apos + 1, NULL, 10) != checksum) // check sum error
		  {
		//	gcode_line_error(PSTR(MSG_ERR_CHECKSUM_MISMATCH));
			Receive_CMD[0].receive_status=0;
		    Receive_CMD[0].receive_len=0;
			return;
		  }
		}
		//else {
		//  gcode_line_error(PSTR(MSG_ERR_NO_CHECKSUM));
		 // return;
		//}

		cmd_pase(Receive_CMD[0].receive_buf,Receive_CMD[0].receive_len);
		Receive_CMD[0].receive_status=0;
		Receive_CMD[0].receive_len=0;


	}
	else
	{
		Receive_CMD[0].receive_buf[Receive_CMD[0].receive_len++] = datar;
		Receive_CMD[0].receive_status=1;
		if(Receive_CMD[0].receive_len>max_rebuf)
			Receive_CMD[0].receive_len=0;

	}


}



void I2C2_EV_IRQHandler(void)
{
    uint32_t  I2CFlagStatus;
    char re_data;
    I2CFlagStatus = I2C_GetLastEvent(I2C2);  // =>  (SR2<<16|SR1)

    if ((I2CFlagStatus & 0x02) != 0)
    { //bit1:addr matched
          if(I2CFlagStatus & 0x80) //bit7 Data register empty (transmitters)
          {//read
        	 // Tx_I2C_num = 0;
               I2C_SendData(I2C2, I2C_Buffer_Tx[Tx_I2C_num]);
               if(I2C_Buffer_Tx[Tx_I2C_num]==0)
                      I2C_Buffer_Tx[0]=0;
          }else
          {
           //  num = 1;
            // I2C_Buffer_Tx[0] = 0;
           //  I2C_Buffer_Rx[0] = 0;
            }
    }
    else if((I2CFlagStatus & 0x80) != 0)
    { // bit7  TxE  -Data register empty (transmitters)
          if((I2CFlagStatus & 0x04)==0){ //bit2  BTF (Byte transfer finished)
        	   Tx_I2C_num++;
               I2C_SendData(I2C2, I2C_Buffer_Tx[Tx_I2C_num]); //printf("I2C status:0x%x\r\n", I2CFlagStatus);
               if(I2C_Buffer_Tx[Tx_I2C_num]==0)
            	   I2C_Buffer_Tx[0]=0;

          }
    }
    else if((I2CFlagStatus & 0x40)&&(I2CFlagStatus & 0x10))
    {  //bit6(RxNE) +  bit4(STOPF)
    	re_data = I2C_ReceiveData(I2C2);    //g_debug_count1++;
    	receing_data(re_data);
        I2C2->CR1 |= 0x1000;//CR1_PEC_Set;
    }else if((I2CFlagStatus & 0x40) != 0){ //bit6  RxNE    -Data register not empty (receivers))
    	  re_data= I2C_ReceiveData(I2C2);
    	  if(re_data!=8)// !register
    		  receing_data(re_data);

    }else if((I2CFlagStatus & 0x10) != 0){ //bit4  STOPF -Stop detection (slave mode)

          I2C2->CR1 |= 0x1000;//CR1_PEC_Set;
          Tx_I2C_num = 0;
    }else{
        //printf("I2C error status:0x%x\r\n", I2CFlagStatus);
    }

	I2C2->SR1=0;
	I2C2->SR2=0;

}


void delay(int dms)
{
	unsigned int old_dms=millis();
	while(1)
	{
		if((millis()-old_dms)>=dms)
			return;
	}

}

static void ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 ;// | GPIO_Pin_5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2 ;//  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA,&GPIO_InitStructure);


}


#if 1//HAS_PID_HEATING

//#define M_PI 3.14159265358979323846
#define _CAT(a, ...) a ## __VA_ARGS__
#define SWITCH_ENABLED_      1

#define ENABLED(b) _CAT(SWITCH_ENABLED_, b)

#define HAS_PID_FOR_BOTH (ENABLED(PIDTEMP) && ENABLED(PIDTEMPBED))

#define NOLESS(v,n) do{ if (v < n) v = n; }while(0)
#define NOMORE(v,n) do{ if (v > n) v = n; }while(0)
#define LIMIT(v,n1,n2) do{ if (v < n1) v = n1; else if (v > n2) v = n2; }while(0)

#define PENDING(NOW,SOON) ((int32_t)(NOW-(SOON))<0)
#define ELAPSED(NOW,SOON) (!PENDING(NOW,SOON))





  /**
   * PID Autotuning (M303)
   *
   * Alternately heat and cool the nozzle, observing its behavior to
   * determine the best PID values to achieve a stable temperature.
   * Needs sufficient heater power to make some overshoot at target
   * temperature to succeed.
   */
void  PID_autotune( int target, int heater, unsigned char ncycles, _Bool set_result/*=false*/)
{
    float current_temp = 0.0;
    int cycles = 0;
    _Bool heating = true;
    long next_temp_ms = millis(), t1 = next_temp_ms, t2 = next_temp_ms,t3 = next_temp_ms;
    long t_high = 0, t_low = 0;
	auto_tune=1;

    long bias, d;
    PID_t tune_pid = { 0, 0, 0 };
    float maxT = 0, minT = 10000;
    const _Bool isbed = 0;// (heater == H_BED);

      #define GHV(B,H) H
      #define SHV(B,H) (/*temp_hotend[heater].*/soft_pwm_amount[heater] = H)
      #define ONHEATINGSTART() //printerEventLEDs.onHotendHeatingStart()
      #define ONHEATING(S,C,T) //printerEventLEDs.onHotendHeating(S,C,T)
      
    if (target > GHV(BED_MAXTEMP - 10, 300 - 15)) {
    //  SERIAL_ECHOLNPGM(MSG_PID_TEMP_TOO_HIGH);
	  sprintf(I2C_Buffer_Tx," PID autotune temp too highh\r");
      return;
    }

//    SERIAL_ECHOLNPGM(MSG_PID_AUTOTUNE_START);
	sprintf(I2C_Buffer_Tx," PID autotune start\r");
    //disable_all_heaters();
    

    SHV(bias = d = (MAX_BED_POWER) >> 1, bias = d = (255) >> 1);

    wait_for_heatup = true; // Can be interrupted with M108
    #if ENABLED(PRINTER_EVENT_LEDS)
      const float start_temp = GHV(temp_bed.celsius, temp_hotend[heater].celsius);
      LEDColor color = ONHEATINGSTART();
    #endif

    #if ENABLED(NO_FAN_SLOWING_IN_PID_TUNING)
      adaptive_fan_slowing = false;
    #endif

    // PID Tuning loop
    while (wait_for_heatup) {

      const long ms = millis();
	  if (ELAPSED(ms, t3 + 1000UL))
	  {
	    t3=ms;
	  	watchdog_reset(); 
	  }
      if (1)
      { // temp sample ready
      //  updateTemperaturesFromRawValues();

        // Get the current temperature and constrain it
        current_temp = GHV(0, Extruder.rel_temper[0]/10.0);
        NOLESS(maxT, current_temp);
        NOMORE(minT, current_temp);



        if (heating && current_temp > target) {
          if (ELAPSED(ms, t2 + 5000UL)) {
            heating = false;
            SHV((bias - d) >> 1, (bias - d) >> 1);
            t1 = ms;
            t_high = t1 - t2;
            maxT = target;
          }
        }

        if (!heating && current_temp < target) {
          if (ELAPSED(ms, t1 + 5000UL)) {
            heating = true;
            t2 = ms;
            t_low = t2 - t1;
            if (cycles > 0) {
              const long max_pow = GHV(255, 255);
              bias += (d * (t_high - t_low)) / (t_low + t_high);
              LIMIT(bias, 20, max_pow - 20);
              d = (bias > max_pow >> 1) ? max_pow - 1 - bias : bias;

            //  SERIAL_ECHOPAIR(MSG_BIAS, bias, MSG_D, d, MSG_T_MIN, minT, MSG_T_MAX, maxT);
			 // sprintf(I2C_Buffer_Tx," s:%d d:%d n:%.2f x:%.2f ls:%d h\r",bias,d,minT,maxT,cycles);
			  
              if (cycles > 2) {
                const float Ku = (4.0f * d) / ( 3.14159265358979323846  * (maxT - minT) * 0.5f),
                            Tu =  (t_low + t_high) * 0.001f,
                            pf = isbed ? 0.2f : 0.6f,
                            df = isbed ? 1.0f / 3.0f : 1.0f / 8.0f;

            //    SERIAL_ECHOPAIR(MSG_KU, Ku, MSG_TU, Tu);
 
                  tune_pid.Kp = Ku * pf;
                  tune_pid.Kd = tune_pid.Kp * Tu * df;
                  tune_pid.Ki = 2 * tune_pid.Kp / Tu;
                //  SERIAL_ECHOLNPGM("\n" MSG_CLASSIC_PID);
                //  SERIAL_ECHOLNPAIR(MSG_KP, tune_pid.Kp, MSG_KI, tune_pid.Ki, MSG_KD, tune_pid.Kd);
                

              }
            }
            SHV((bias + d) >> 1, (bias + d) >> 1);
            cycles++;
            minT = target;
          }
        }
      }

      // Did the temperature overshoot very far?
      #ifndef MAX_OVERSHOOT_PID_AUTOTUNE
        #define MAX_OVERSHOOT_PID_AUTOTUNE 30
      #endif
      if (current_temp > target + MAX_OVERSHOOT_PID_AUTOTUNE) {
       // SERIAL_ECHOLNPGM(MSG_PID_TEMP_TOO_HIGH);
		sprintf(I2C_Buffer_Tx,"AUTOTUNE_TEMP_TOO_HIGH h\n");
        break;
      }

      // Report heater states every 2 seconds
      if (ELAPSED(ms, next_temp_ms)) {
        next_temp_ms = ms + 2000UL;

        // Make sure heating is actually working
      } // every 2 seconds

      // Timeout after MAX_CYCLE_TIME_PID_AUTOTUNE minutes since the last undershoot/overshoot cycle
      #ifndef MAX_CYCLE_TIME_PID_AUTOTUNE
        #define MAX_CYCLE_TIME_PID_AUTOTUNE 20L
      #endif
      if (((ms - t1) + (ms - t2)) > (MAX_CYCLE_TIME_PID_AUTOTUNE * 60L * 1000L)) {
     //   SERIAL_ECHOLNPGM(MSG_PID_TIMEOUT);
		sprintf(I2C_Buffer_Tx,"AUTOTUNE_TIMEOUT h\n");
		
        break;
      }

      if (cycles > ncycles && cycles > 2) {
      //  SERIAL_ECHOLNPGM(MSG_PID_AUTOTUNE_FINISHED);

          //say_default_(); SERIAL_ECHOLNPAIR("Kp ", tune_pid.Kp);
         // say_default_(); SERIAL_ECHOLNPAIR("Ki ", tune_pid.Ki);
         // say_default_(); SERIAL_ECHOLNPAIR("Kd ", tune_pid.Kd);

		  sprintf(I2C_Buffer_Tx," AUTOTUNE_FINISHED Kp:%.4f;Ki:%.4f;Kd:%.4f h\n",tune_pid.Kp,tune_pid.Ki,tune_pid.Kd);

          delay(1000);    
		  sprintf(I2C_Buffer_Tx,"\n AUTOTUNE_FINISHED Kp:%.4f;Ki:%.4f;Kd:%.4f (M301 P%.4f I%.4f D%.4f) h\n",tune_pid.Kp,tune_pid.Ki,tune_pid.Kd,
		  	tune_pid.Kp,tune_pid.Ki,tune_pid.Kd);
		  
		break;
      }
    //  ui.update();
    }

  //  disable_all_heaters();
  auto_tune=0;

      return;
  }

#endif // HAS_PID_HEATING
#define FAN0_PIN   GPIO_Pin_8
#define FAN1_PIN   GPIO_Pin_9
#define FAN2_PIN   GPIO_Pin_10
#define FAN3_PIN   GPIO_Pin_7
#define constrain(	a,	b,	c)	 (a>b?a:b)<c?(a>b?a:b):c

void TIM2_IRQHandler(void)
{
  ms_count_n++;
  constrain(Extruder.tar_temper[0], 0, 2900);
  constrain(Extruder.tar_temper[1], 0, 2900);
  constrain(Bed_tmper.tar_temper, 0, 1500);
  /////
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
	////////////////////extruder
	if((ms_count_n%4)==0)
	{
		Extruder.rel_temper[0]=Get_Temperature(0)*10;
		Extruder.rel_temper[1]=Get_Temperature(2)*10;
		Bed_tmper.rel_temper=Get_Temperature(1)*10;
	}
	if(Extruder.rel_temper[0]<=0)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	}
	if(Extruder.rel_temper[1]<=0)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_12);
	}
	if(Bed_tmper.rel_temper<=0)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	}
	////////////////////////hotend fan
	if(Extruder.rel_temper[0]>600)
	{
		GPIO_SetBits(GPIOA,FAN0_PIN);//Fan0   //hotend fan
		//GPIO_SetBits(GPIOA,FAN1_PIN);//Fan1
		//GPIO_SetBits(GPIOA,FAN2_PIN);//Fan2
	}
	else
		GPIO_ResetBits(GPIOA,FAN0_PIN);
	///////////blower Fan
	if(1)
	{
		static unsigned char fan0=0;

		if(fan0==Extruder.fan0[0])
			GPIO_ResetBits(GPIOA,FAN1_PIN);
		else if(fan0==0)
		{
			GPIO_SetBits(GPIOA,FAN1_PIN);
		}
		fan0++;
	}

	///////////////board Fan
	/*if(Extruder.fan2[0])//(Extruder.rel_temper>600||Extruder.fan0>80||Extruder.fan1>80)
	{
		GPIO_SetBits(GPIOA,FAN2_PIN);
	}
	else
		GPIO_ResetBits(GPIOA,FAN2_PIN);*/
	/////////
	///////////  Fan2_board Fan
	if(1)
	{
		static unsigned char fan2=0;
		if(fan2==Extruder.fan2[0])
			GPIO_ResetBits(GPIOA,FAN2_PIN);
		else if(fan2==0)
		{
			GPIO_SetBits(GPIOA,FAN2_PIN);
		}
		fan2++;
	}
	/////////

	///////////  Fan3
	if(1)
	{
		static unsigned char fan1=0;

		if(fan1==Extruder.fan1[0])
			GPIO_ResetBits(GPIOB,FAN3_PIN);
		else if(fan1==0)
		{
			GPIO_SetBits(GPIOB,FAN3_PIN);
		}
		fan1++;
	}
	/////////

/*
	if(Extruder.rel_temper>0)
	{
		if(Extruder.rel_temper>Extruder.tar_temper)
		{
			GPIO_ResetBits(GPIOB,GPIO_Pin_12);
			//GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		}
		else
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_12);
			//GPIO_SetBits(GPIOC,GPIO_Pin_13);
		}
	}*/
/////////////bed
	if(Bed_tmper.rel_temper>0)
	{
		if(Bed_tmper.rel_temper>Bed_tmper.tar_temper)
			GPIO_ResetBits(GPIOB,GPIO_Pin_13);
		else
			GPIO_SetBits(GPIOB,GPIO_Pin_13);
	}

	pid_calc();
//////////
	if(Extruder.rel_temper[0]>0)
	{



		//////////////////////////////
		static int runaway=0,old_rel=0,cnt=0;
		if(Extruder.tar_temper[0]>10)
			runaway++;
		if(runaway>10000)
		{
			runaway=0;
			if((Extruder.tar_temper[0]-Extruder.rel_temper[0])>100)
			{


				if((Extruder.rel_temper[0]-old_rel)<=30)
				{
					cnt++;
					if(cnt>=2)
					{
			 		 //  Extruder.tar_temper=0;
			 		   cnt=0;
			 		//  sprintf(I2C_Buffer_Tx,"run away\n");
					}
				}
				else
					cnt=0;
				old_rel=Extruder.rel_temper[0];
			}

		}
#if 0
	    ////////////////////
		if(Extruder.hightime>=100)
			GPIO_SetBits(GPIOB,GPIO_Pin_12);//heat
		  else if(Extruder.hightime==0)
			  GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		  else
		  {
			  Extruder.count++;
			  if(Extruder.count<=(Extruder.hightime))
			  {

				 GPIO_SetBits(GPIOB,GPIO_Pin_12);//heat
			  }
			  else if(Extruder.count<=100)
			  {

				GPIO_ResetBits(GPIOB,GPIO_Pin_12);
			  }
			  else
			  {
				  Extruder.count=0;
				  GPIO_ResetBits(GPIOB,GPIO_Pin_12);
			  }
		  }
#endif
	}

	/////////////////////
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);

  }
}

void heat_pin_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	///heat
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|FAN3_PIN;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	////////////// init Fan0~2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = FAN0_PIN|FAN1_PIN|FAN2_PIN|GPIO_Pin_12;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/////////
	GPIO_ResetBits(GPIOA,FAN0_PIN);
	GPIO_ResetBits(GPIOA,FAN1_PIN);
	GPIO_ResetBits(GPIOA,FAN2_PIN);
	GPIO_ResetBits(GPIOB,FAN3_PIN);
	GPIO_ResetBits(GPIOA,GPIO_Pin_12);// heater1
/*
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //使能PB,PE端口时钟
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	*/
//GPIO_ResetBits(LED0_PORT,LED0_PIN)
//GPIO_SetBits(LED0_PORT,LED0_PIN)
	////////////PA14  SWD CLK  for filament sensor
	//

}


void swd_gpio_init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
#define PAGE_SIZE 0x400
static u32 FLASH_PagesMask(vu32 Size)
{
    u32 pagenumber = 0x0;
    u32 size = Size;

    if ((size % PAGE_SIZE) != 0)
    {
        pagenumber = (size / PAGE_SIZE) + 1;
    }
    else
    {
        pagenumber = size / PAGE_SIZE;
    }
    return pagenumber;
}
void FLASH_ProgramStart(void)
{
    FLASH_Status FLASHStatus = FLASH_COMPLETE;
    u32 NbrOfPage = 0;
    vu32 EraseCounter = 0;

    FLASH_Unlock();
//    m_EraseCounter = 0;

    NbrOfPage = FLASH_PagesMask(100000);
    for (; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
    {
        FLASHStatus = FLASH_ErasePage(0x8003000 + (PAGE_SIZE * EraseCounter));
    }
}


// Initialize watchdog with 8s timeout, if possible. Otherwise, make it 4s.
void watch_dog_init() {

// Tout=((4*2^prer)*rlr)/40 (ms).

#define LSI_FREQ   40000/16//40000/32

 /*Enables write access to IWDG_PR and IWDG_RLR registers */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    /*Set prescaler value*/
    IWDG_SetPrescaler(IWDG_Prescaler_64);
    /*Set reload value
    Counter Reload Value = 250ms/IWDG counter clock period
                          = 250ms / (LSI/32)
                          = 0.25s / (LsiFreq/32)
                          = LsiFreq/(32 * 4)
                          = LsiFreq/128
   */
    IWDG_SetReload(LSI_FREQ);
    /*Download reload value to register*/
    IWDG_ReloadCounter();
	IWDG_Enable();

  //delay(10000); // test it!
}
void watchdog_reset() 
{
	IWDG_ReloadCounter();
}


int
main(int argc, char* argv[])
{

//	SystemInit();
//NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0000);//app base addr
	//asm("CPSIE  I");
	

	NVIC_Configuration();

	unsigned char data1[100];
	char swd_init=0;
	Servo_Timer_Config();
	ADC_GPIO_Config();
	heat_pin_init();
	ADC_Mode_Config();

	IIC_Init();
	Pid_init();
	Extruder.tar_temper[0]=0;
	Extruder.tar_temper[1]=0;
	data1[0]='h';
	data1[1]='l';
	data1[2]='o';
	data1[3]='p';
	Extruder.fan3[0]=0;
	Extruder.fan2[0]=0;
	Extruder.fan1[0]=0;
	Extruder.fan0[0]=0;
  // Infinite loop
	PID_t tune_pid = { 10.0, 6.3, 365.3 };
	sprintf(I2C_Buffer_Tx,"T:1C\n");
//	FLASH_ProgramStart();
	tune_start=0;
    watch_dog_init();
    while (1)
    {
    	if(swd_init==0&&Extruder.tar_temper[0]>1200)
    	{
    		swd_init=1;
    		swd_gpio_init();//disable st link swd pins
    	}
		if(tune_start)
		{
			PID_autotune(tune_temp, tune_e, tune_c, tune_u);
			tune_start=0;
		}
         watchdog_reset();
		
	//  Raspberry_Send_Datas(data1,4);
	//  Recive_RXD_Deal();
    }
  // Infinite loop, never return.
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

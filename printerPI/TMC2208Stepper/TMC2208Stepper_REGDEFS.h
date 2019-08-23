#ifndef TMC2208Stepper_REGDEFS_h
#define TMC2208Stepper_REGDEFS_h

#define TMC2208_READ 		0x00
#define TMC2208_WRITE 		0x80
#define TMC2208_SYNC 		0x05
#define TMC2208_SLAVE_ADDR	0x00

// Register memory positions
#define REG_GCONF 			0x00
#define REG_GSTAT 			0x01
#define REG_IFCNT 			0x02
#define REG_SLAVECONF 		0x03
#define REG_OTP_PROG 		0x04
#define REG_OTP_READ 		0x05
#define REG_IOIN 			0x06
#define REG_FACTORY_CONF 	0x07
#define REG_IHOLD_IRUN 		0x10
#define REG_TPOWERDOWN 		0x11
#define REG_TSTEP 			0x12
#define REG_TPWMTHRS 		0x13
#define REG_VACTUAL 		0x22
#define REG_MSCNT 			0x6A
#define REG_MSCURACT 		0x6B
#define REG_CHOPCONF 		0x6C
#define REG_DRV_STATUS 		0x6F
#define REG_PWMCONF 		0x70
#define REG_PWM_SCALE 		0x71
#define REG_PWM_AUTO 		0x72

// GCONF
#define I_SCALE_ANALOG_bp	0
#define INTERNAL_RSENSE_bp	1
#define EN_SPREADCYCLE_bp	2
#define SHAFT_bp			3
#define INDEX_OTPW_bp		4
#define INDEX_STEP_bp		5
#define PDN_DISABLE_bp		6
#define MSTEP_REG_SELECT_bp	7
#define MULTISTEP_FILT_bp	8
#define I_SCALE_ANALOG_bm	0b1ul
#define INTERNAL_RSENSE_bm	0b10ul
#define EN_SPREADCYCLE_bm	0b100ul
#define SHAFT_bm			0b1000ul
#define INDEX_OTPW_bm		0b10000ul
#define INDEX_STEP_bm		0b100000ul
#define PDN_DISABLE_bm		0b1000000ul
#define MSTEP_REG_SELECT_bm	0b10000000ul
#define MULTISTEP_FILT_bm	0b100000000ul
// GSTAT
#define RESET_bp 			0
#define DRV_ERR_bp			1
#define UV_CP_bp			2
#define RESET_bm 			0b1ul
#define DRV_ERR_bm			0b10ul
#define UV_CP_bm			0b100ul
// IFCNT
#define IFCNT_bp			0
#define IFCNT_bm			0xFFul
// SLAVECONF
#define SLAVECONF_bp		0
#define SLAVECONF_bm		0xF00ul
#define SENDDELAY_bp		8
#define SENDDELAY_bm		0xF00ul
// OTP_PROG
#define OTPBIT_bp			0
#define OTPBYTE_bp			4
#define OTPMAGIC_bp			8
#define OTPBIT_bm			0b111ul
#define OTPBYTE_bm			0b110000ul
#define OTPMAGIC_bm			0b1111111100000000ul
// OTP_READ
#define OTP0_bp				0
#define OTP1_bp				8
#define OTP2_bp			   16
#define OTP0_bm				0xFFul
#define OTP1_bm				0xFF00ul
#define OTP2_bm			    0xFF0000ul
// IOIN
#define ENN_bp				0
#define MS1_bp				2
#define MS2_bp				3
#define DIAG_bp				4
#define PDN_UART_bp			6
#define STEP_bp 			7
#define SEL_A_bp 			8
#define DIR_bp				9
#define VERSION_bp		   24
#define ENN_bm				0b1ul
#define MS1_bm				0b100ul
#define MS2_bm				0b1000ul
#define DIAG_bm				0b10000ul
#define PDN_UART_bm			0b1000000ul
#define STEP_bm 			0b10000000ul
#define SEL_A_bm 			0b100000000ul
#define DIR_bm				0b1000000000ul
#define VERSION_bm			0xFF000000ul
// FACTORY_CONF
#define FCLKTRIM_bp			0
#define OTTRIM_bp			8
#define FCLKTRIM_bm			0x1Ful
#define OTTRIM_bm			0x300ul
// IHOLD_IRUN
#define IHOLD_bp 			0
#define IRUN_bp				8
#define IHOLDDELAY_bp	   16
#define IHOLD_bm 			0x1Ful
#define IRUN_bm				0x1F00ul
#define IHOLDDELAY_bm	    0xF0000ul
// TPOWERDOWN
#define TPOWERDOWN_bp		0
#define TPOWERDOWN_bm		0xFFul
// MSCURACT
#define CUR_A_bp			0
#define CUR_B_bp		   16
#define CUR_A_bm			0x1FFul
#define CUR_B_bm			0x1FF0000ul
// PWM_SCALE
#define PWM_SCALE_SUM_bp	0
#define PWM_SCALE_AUTO_bp  16
#define PWM_SCALE_SUM_bm	0xFFul
#define PWM_SCALE_AUTO_bm 	0x1FF0000ul
// PWM_AUTO
#define PWM_OFS_AUTO_bp		0
#define PWM_GRAD_AUTO_bp   16
#define PWM_OFS_AUTO_bm		0xFFul
#define PWM_GRAD_AUTO_bm 	0xFF0000ul
// OTP_READ
#define OTP_FCLKTRIM_bp		0
#define OTP_OTTRIM_bp		5
#define OTP_INTERNALRSENSE_bp 6
#define OTP_TBL_bp 			7
#define OTP_PWM_GRAD_bp		8
#define OTP_PWM_AUTOGRAD_bp 12
#define OTP_CHOPCONF_bp	   12
#define OTP_TPWMTHRS_bp	   13
#define OTP_PWM_OFS_bp	   16
#define OTP_PWM_REG_bp	   17
#define OTP_OTP_PWM_FREQ_bp 18
#define OTP_IHOLDDELAY_bp  19
#define OTP_IHOLD_bp 	   21
#define OTP_OTP_EN_SPREADCYCLE 23
// CHOPCONF
#define TOFF_bp				0
#define HSTRT_bp			4
#define HEND_bp				7
#define TBL_bp 			   15
#define VSENSE_bp		   17
#define MRES_bp 		   24
#define INTPOL_bp		   28
#define DEDGE_bp		   29
#define DISS2G_bp		   30
#define DISS2VS_bp		   31
#define TOFF_bm			  	0xFul
#define HSTRT_bm		 	0x70ul
#define HEND_bm				0x780ul
#define TBL_bm		  		0x18000ul
#define VSENSE_bm	  		0x20000ul
#define MRES_bm				0xF000000ul
#define INTPOL_bm  			0x10000000ul
#define DEDGE_bm   			0x20000000ul
#define DISS2G_bm  			0x40000000ul
#define DISS2VS_bm 			0x80000000ul
// PWMCONF
#define PWM_OFS_bp 			0
#define PWM_GRAD_bp 		8
#define PWM_FREQ_bp 	   16
#define PWM_AUTOSCALE_bp   18
#define PWM_AUTOGRAD_bp    19
#define FREEWHEEL_bp 	   20
#define PWM_REG_bp 		   24
#define PWM_LIM_bp		   28
#define PWM_OFS_bm 			0xFFul
#define PWM_GRAD_bm 		0xFF00ul
#define PWM_FREQ_bm 	    0x30000ul
#define PWM_AUTOSCALE_bm    0x40000ul
#define PWM_AUTOGRAD_bm     0x80000ul
#define FREEWHEEL_bm 	    0x300000ul
#define PWM_REG_bm 		    0xF000000ul
#define PWM_LIM_bm		    0xF0000000ul
// DRV_STATUS
#define OTPW_bp 			0
#define OT_bp 				1
#define S2GA_bp				2
#define S2GB_bp				3
#define S2VSA_bp			4
#define S2VSB_bp			5
#define OLA_bp 				6
#define OLB_bp 				7
#define T120_bp				8
#define T143_bp				9
#define T150_bp			   10
#define T157_bp			   11
#define CS_ACTUAL_bp	   16
#define STEALTH_bp		   30
#define STST_bp			   31
#define OTPW_bm 			0b1ul
#define OT_bm 				0b10ul
#define S2GA_bm				0b100ul
#define S2GB_bm				0b1000ul
#define S2VSA_bm			0b10000ul
#define S2VSB_bm			0b100000ul
#define OLA_bm 				0b1000000ul
#define OLB_bm 				0b10000000ul
#define T120_bm				0b100000000ul
#define T143_bm				0b1000000000ul
#define T150_bm			    0b10000000000ul
#define T157_bm			    0b100000000000ul
#define CS_ACTUAL_bm	    0x1F0000ul
#define STEALTH_bm		    0x40000000ul
#define STST_bm			    0x80000000ul

#endif

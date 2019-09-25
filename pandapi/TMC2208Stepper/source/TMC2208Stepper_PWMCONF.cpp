#include "../TMC2208Stepper.h"
#include "TMC2208Stepper_MACROS.h"

// PWMCONF
bool TMC2208Stepper::PWMCONF(uint32_t *data) {
	if (write_only) {
		*data = PWMCONF_sr;
		return 0;
	}
	REGISTER_R(PWMCONF);
}
void TMC2208Stepper::PWMCONF(uint32_t input) {
	PWMCONF_sr = input;
	REGISTER_W(PWMCONF);
}

void TMC2208Stepper::pwm_ofs		( uint8_t B ) { MOD_REG(PWMCONF, PWM_OFS); 		}
void TMC2208Stepper::pwm_grad		( uint8_t B ) { MOD_REG(PWMCONF, PWM_GRAD); 	}
void TMC2208Stepper::pwm_freq		( uint8_t B ) { MOD_REG(PWMCONF, PWM_FREQ); 	}
void TMC2208Stepper::pwm_autoscale	( bool 	  B ) { MOD_REG(PWMCONF, PWM_AUTOSCALE);}
void TMC2208Stepper::pwm_autograd	( bool    B ) { MOD_REG(PWMCONF, PWM_AUTOGRAD); }
void TMC2208Stepper::freewheel		( uint8_t B ) { MOD_REG(PWMCONF, FREEWHEEL); 	}
void TMC2208Stepper::pwm_reg		( uint8_t B ) { MOD_REG(PWMCONF, PWM_REG); 		}
void TMC2208Stepper::pwm_lim		( uint8_t B ) { MOD_REG(PWMCONF, PWM_LIM); 		}

uint8_t TMC2208Stepper::pwm_ofs()		{ GET_BYTE(PWMCONF, PWM_OFS);		}
uint8_t TMC2208Stepper::pwm_grad()		{ GET_BYTE(PWMCONF, PWM_GRAD);		}
uint8_t TMC2208Stepper::pwm_freq()		{ GET_BYTE(PWMCONF, PWM_FREQ);		}
bool 	TMC2208Stepper::pwm_autoscale()	{ GET_BYTE(PWMCONF, PWM_AUTOSCALE);	}
bool 	TMC2208Stepper::pwm_autograd()	{ GET_BYTE(PWMCONF, PWM_AUTOGRAD);	}
uint8_t TMC2208Stepper::freewheel()		{ GET_BYTE(PWMCONF, FREEWHEEL);		}
uint8_t TMC2208Stepper::pwm_reg()		{ GET_BYTE(PWMCONF, PWM_REG);		}
uint8_t TMC2208Stepper::pwm_lim()		{ GET_BYTE(PWMCONF, PWM_LIM);		}

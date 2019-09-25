#include "../TMC2208Stepper.h"
#include "TMC2208Stepper_MACROS.h"

// GCONF
bool TMC2208Stepper::GCONF(uint32_t *data) {
	if (write_only) {
		*data = GCONF_sr;
		return 0;
	}
	REGISTER_R(GCONF);
}
void TMC2208Stepper::GCONF(uint32_t input) {
	GCONF_sr = input;
	REGISTER_W(GCONF);
}


void TMC2208Stepper::I_scale_analog(bool B)		{ MOD_REG(GCONF, I_SCALE_ANALOG);	}
void TMC2208Stepper::internal_Rsense(bool B)	{ MOD_REG(GCONF, INTERNAL_RSENSE);	}
void TMC2208Stepper::en_spreadCycle(bool B)		{ MOD_REG(GCONF, EN_SPREADCYCLE);	}
void TMC2208Stepper::shaft(bool B) 				{ MOD_REG(GCONF, SHAFT);			}
void TMC2208Stepper::index_otpw(bool B)			{ MOD_REG(GCONF, INDEX_OTPW);		}
void TMC2208Stepper::index_step(bool B)			{ MOD_REG(GCONF, INDEX_STEP);		}
void TMC2208Stepper::pdn_disable(bool B)		{ MOD_REG(GCONF, PDN_DISABLE);		}
void TMC2208Stepper::mstep_reg_select(bool B)	{ MOD_REG(GCONF, MSTEP_REG_SELECT);	}
void TMC2208Stepper::multistep_filt(bool B)		{ MOD_REG(GCONF, MULTISTEP_FILT);	}

bool TMC2208Stepper::I_scale_analog()	{ GET_BYTE(GCONF, I_SCALE_ANALOG);	}
bool TMC2208Stepper::internal_Rsense()	{ GET_BYTE(GCONF, INTERNAL_RSENSE);	}
bool TMC2208Stepper::en_spreadCycle()	{ GET_BYTE(GCONF, EN_SPREADCYCLE);	}
bool TMC2208Stepper::shaft()			{ GET_BYTE(GCONF, SHAFT);			}
bool TMC2208Stepper::index_otpw()		{ GET_BYTE(GCONF, INDEX_OTPW);		}
bool TMC2208Stepper::index_step()		{ GET_BYTE(GCONF, INDEX_STEP);		}
bool TMC2208Stepper::pdn_disable()		{ GET_BYTE(GCONF, PDN_DISABLE);		}
bool TMC2208Stepper::mstep_reg_select()	{ GET_BYTE(GCONF, MSTEP_REG_SELECT);}
bool TMC2208Stepper::multistep_filt()	{ GET_BYTE(GCONF, MULTISTEP_FILT);	}

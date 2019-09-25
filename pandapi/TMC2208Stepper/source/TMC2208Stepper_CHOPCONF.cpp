#include "../TMC2208Stepper.h"
#include "TMC2208Stepper_MACROS.h"

// CHOPCONF
void TMC2208Stepper::CHOPCONF(uint32_t input) {
	CHOPCONF_sr = input;
	REGISTER_W(CHOPCONF);
}
bool TMC2208Stepper::CHOPCONF(uint32_t *data) {
	if (write_only) {
		*data = CHOPCONF_sr;
		return 0;
	}
	REGISTER_R(CHOPCONF);
}
void TMC2208Stepper::toff	( uint8_t  B )	{ MOD_REG(CHOPCONF, TOFF); 		}
void TMC2208Stepper::hstrt	( uint8_t  B )	{ MOD_REG(CHOPCONF, HSTRT); 	}
void TMC2208Stepper::hend	( uint8_t  B )	{ MOD_REG(CHOPCONF, HEND); 		}
void TMC2208Stepper::tbl	( uint8_t  B )	{ MOD_REG(CHOPCONF, TBL); 		}
void TMC2208Stepper::vsense	( bool     B )	{ MOD_REG(CHOPCONF, VSENSE); 	}
void TMC2208Stepper::mres	( uint8_t  B )	{ MOD_REG(CHOPCONF, MRES); 		}
void TMC2208Stepper::intpol	( bool     B )	{ MOD_REG(CHOPCONF, INTPOL); 	}
void TMC2208Stepper::dedge	( bool     B )	{ MOD_REG(CHOPCONF, DEDGE);  	}
void TMC2208Stepper::diss2g	( bool     B )	{ MOD_REG(CHOPCONF, DISS2G); 	}
void TMC2208Stepper::diss2vs( bool     B )	{ MOD_REG(CHOPCONF, DISS2VS);	}

uint8_t TMC2208Stepper::toff()		{ GET_BYTE(CHOPCONF, TOFF); 	}
uint8_t TMC2208Stepper::hstrt()		{ GET_BYTE(CHOPCONF, HSTRT); 	}
uint8_t TMC2208Stepper::hend()		{ GET_BYTE(CHOPCONF, HEND); 	}
uint8_t TMC2208Stepper::tbl()		{ GET_BYTE(CHOPCONF, TBL); 		}
bool 	TMC2208Stepper::vsense()	{ GET_BYTE(CHOPCONF, VSENSE); 	}
uint8_t TMC2208Stepper::mres()		{ GET_BYTE(CHOPCONF, MRES); 	}
bool 	TMC2208Stepper::intpol()	{ GET_BYTE(CHOPCONF, INTPOL); 	}
bool 	TMC2208Stepper::dedge()		{ GET_BYTE(CHOPCONF, DEDGE);  	}
bool 	TMC2208Stepper::diss2g()	{ GET_BYTE(CHOPCONF, DISS2G); 	}
bool 	TMC2208Stepper::diss2vs()	{ GET_BYTE(CHOPCONF, DISS2VS);	}

void TMC2208Stepper::hysteresis_end(int8_t value) { hend(value+3); }
int8_t TMC2208Stepper::hysteresis_end() { return hend()-3; };

void TMC2208Stepper::hysteresis_start(uint8_t value) { hstrt(value-1); }
uint8_t TMC2208Stepper::hysteresis_start() { return hstrt()+1; }

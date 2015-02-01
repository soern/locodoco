#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "config.h"

//#include "rfm12/src/rfm12.h"
#include "rfm12.h"
#include "motor.h"
#include "adc.h"
#include "locodoco.h"
#include "os.h"

int main (void)
{
	MCUCR = _BV(IVCE);
	MCUCR = 0x00;
	MCUSR = 0x00;

	ldc_header_t tst;

	//SENSE_SPEED_SETUP();
	SENSE_INC();
	motor_init();
	LIGHTS_INIT();
	rfm12_init();
	_delay_ms(100);
	//LIGHT_CABIN_ON();
	rfm12_init();
	LIGHT_RW_ON();
	sei();
	
	tst.addr = 0x01;
	tst.ltype = LDC_CMD_EHLO;
	rfm12_tx (sizeof(ldc_header_t), LDC_TYPE, (uint8_t*) &tst);

	PORT_LIGHT_CABIN ^= (PIN_LIGHT_CABIN);
	motor_set_direction(MOTOR_DIR_RW);

	while (23)
	{
		rfm12_tick();
		motor_tick();
		os_idle_tick();
		ldc_packet_handler();
	}
}

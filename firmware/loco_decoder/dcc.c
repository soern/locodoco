#include "dcc.h"

static uint8_t dcc_mask;
static uint8_t dcc_byte;
static uint8_t dcc_buf[DCC_NUM_BYTES];

void dcc_init()
{
	DCC_INT_SETUP();
	DDR_DCC |= PIN_DCC;
	PORT_DCC &= ~(PIN_DCC); /* disable pullup */
	
	dcc_byte = 0;
	dcc_mask = 0x01; /* DCC is LSB first */
}

void dcc_counter()
{
	/* low -> high change; start counting */
	if (PORT_DCC & PIN_DCC)
	{
		return;
	}

}

/* run from ISR - needs to be as fast as possible */
void dcc_read_bit()
{
	dcc_mask <<= 1;
	if (dcc_mask)
		return;
	
	dcc_mask = 0x01;
	dcc_byte++;
	dcc_byte %= DCC_NUM_BYTES;
}

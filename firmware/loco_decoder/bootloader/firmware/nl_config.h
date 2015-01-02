#ifndef NL_CONFIG_H
#include <avr/wdt.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

/* Maximum size of packets transmitted and received by this
 * bootloader.
 */
#define NL_PACKETSIZE SPM_PAGESIZE+5

/* the position in the eeprom where the device's network address is stored at */
#define NL_ADDRESSPOS 0

/* define how many bytes to use for the address field. this will also add approx. 50 bytes
 * to the binary (!)
 **/
#define NL_ADDRESSSIZE 1

/* if the counter value masked by the NL_RETRANSMIT_MASK equals 0, the last command is repeated.
 * this value should be significantly lower than NL_MAXCOUNT. (i.e. 1/16th)
 */
#define NL_RETRANSMIT_MASK ((uint32_t) 0xfffff)

/* the maximum counter value before the nakkaloader starts booting the application.
 */
#define NL_MAXCOUNT 0x3fffff

/* set verbosity for bootloader (0 to 2)
 *
 * setting this to values greater than 0 will add a few bytes to the binary.
 *
 * Verbosity Levels:
 *
 * 0 - STFU-Level - don't even complain on errors.
 * 1 - Complain on errors
 * 2 - Send additional debug information
 *
 * */
#define NL_VERBOSITY 0

#define NL_CONDITION_SET 1
inline uint8_t nl_bootloader_condition ();
inline uint8_t nl_bootloader_condition ()
{
	/* virgin firmware */
	if (pgm_read_word(0x00) == 0xffff)
		return 1;
	
	if (MCUSR & (_BV(WDRF) | _BV(PORF)) != (_BV(WDRF) | _BV(PORF)))
	{
		/* normal wdt reset */
		return 0;
	}
	
	cli();
	/* PORF and WDT reset flag set -> start bootloader */
	wdt_reset();
	MCUSR = 0x00;
	WDTCSR |= (_BV(WDCE) | _BV(WDE));
	WDTCSR = 0x00;

	return 1;
}

#endif

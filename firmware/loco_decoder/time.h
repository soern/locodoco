#include <stdint.h>
#include <avr/interrupt.h>
#pragma once

/* get time 20�s step counter value */
inline uint16_t time_get_20us ();

void time_init(void);

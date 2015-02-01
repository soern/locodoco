#include "time.h"

volatile static uint16_t us20_count;
	
inline uint16_t time_get_20us ()
{
	return us20_count;
}

void time_init()
{
	us20_count = 0;
}

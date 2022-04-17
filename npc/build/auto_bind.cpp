#include <nvboard.h>
#include "Vtop.h"

void nvboard_bind_all_pins(Vtop* top) {
	nvboard_bind_pin( &top->s, BIND_RATE_SCR, BIND_DIR_IN , 2, SW1, SW0);
	nvboard_bind_pin( &top->y, BIND_RATE_SCR, BIND_DIR_OUT, 2, LD1, LD0);
	nvboard_bind_pin( &top->a, BIND_RATE_SCR, BIND_DIR_IN , 8, SW9, SW8, SW7, SW6, SW5, SW4, SW3, SW2);
}

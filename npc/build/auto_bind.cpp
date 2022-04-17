#include <nvboard.h>
#include "Vtop.h"

void nvboard_bind_all_pins(Vtop* top) {
	nvboard_bind_pin( &top->s, BIND_RATE_SCR, BIND_DIR_IN , 2, SW0, SW1);
	nvboard_bind_pin( &top->y, BIND_RATE_SCR, BIND_DIR_OUT, 4, LD0, LD1, LD2, LD3);
}

#include <stdint.h>

volatile uint32_t g_uTick = 0;
#define  UNIT_TICK	(1)

__attribute__((weak)) void HAL_IncTick(void)
{
	g_uTick += UNIT_TICK;
}

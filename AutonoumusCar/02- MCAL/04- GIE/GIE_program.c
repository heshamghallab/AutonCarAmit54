#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_interface.h"
#include "GIE_config.h"
#include "GIE_private.h"


void GIE_vidEnableGlobalInterrupt(void)
{
	SET_BIT(SREG,7);
}

void GIE_vidDisableGlobalInterrupt(void)
{
	CLR_BIT(SREG,7);
}
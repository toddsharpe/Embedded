#include "Stm32/SysCfg.h"

#include <stm32f7xx.h>
#include <stm32f746xx.h>

using namespace Stm32;

void SysCfg::Init()
{
	//Enable clock
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);
	__DSB();
	
	//Select RMII mode
	SET_BIT(SYSCFG->PMC, SYSCFG_PMC_MII_RMII_SEL);

	//Dummy read of 
	(void)SYSCFG->PMC;
}

#include <stm32f401xc.h>
#include "Board.h"
#include "Buffer.h"
#include "Stm32/Rcc.h"
#include "Stm32/Pll.h"
#include "Stm32/SystemClock.h"
#include "Stm32/Boards/STEval-FCU001V2.h"
#include "RTT/SEGGER_RTT.h"
#include "Util.h"

using namespace Stm32;

namespace Board
{
	//Peripheral configuration
	static constexpr PllConfig const PllConfig84MHz =
	{
		.Source = PllSrc::HSE,
		.M = 16,
		.N = 336,
		.P = PllDiv::Div4,
		.Q = 7
	};

	//84MHz SYS, 42Hz APB1, 84MHz APB2
	static constexpr SystemClockConfig const SysClock84MHz =
	{
		.Source = RCC_CFGR_SW_PLL,
		.AHBCLKDivider = RCC_CFGR_HPRE_DIV1,
		.APB1CLKDivider = RCC_CFGR_PPRE1_DIV2,
		.APB2CLKDivider = RCC_CFGR_PPRE2_DIV1,
		.FlashLatency = FLASH_ACR_LATENCY_5WS
	};

	static constexpr GpioPinConfig const GpioMotor =
	{
		.Mode = GpioMode::Alternate,
		.OutputType = GpioOutputType::PushPull,
		.PullType = GpioPullType::None,
		.Speed = GpioSpeed::Low,
		.Alternate = GpioAlternate::Tim4
	};

	// 500Hz PWM cycles
	static constexpr PwmConfig const MotorConfig =
	{
		.Period = 2000,
		.Ch1Enabled = true,
		.Ch2Enabled = true,
		.Ch3Enabled = true,
		.Ch4Enabled = true,
	};

	Rcc rcc(16'000'000, 16'000'000);
	GpioPin Led1(GPIOB, 5);
	GpioPin Led2(GPIOB, 4);

	//Motor controls
	/**
	 * TIM4 GPIO Configuration
	* PB6 ------> TIM4_CH1
	* PB7 ------> TIM4_CH2
	* PB8 ------> TIM4_CH3
	* PB9 ------> TIM4_CH4
	*/
	GpioPin motor1(GPIOB, 6);
	GpioPin motor2(GPIOB, 7);
	GpioPin motor3(GPIOB, 8);
	GpioPin motor4(GPIOB, 9);
	Pwm motor_pwm(TIM4);
	
	void Init()
	{
		//Initialize peripherals
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
		SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM4EN);
		__DSB();
		
		//Initialize system: PLL, System Clock, SysCfg
		Pll::Init(PllConfig84MHz);
		SystemClock::Init(SysClock84MHz);
		Board::Printf("Board: STEval-FCU001V2\r\n");

		//Initialize LEDs
		Led1.Init(GpioOutput);
		Led2.Init(GpioOutput);

		//Initialize motors
		motor1.Init(GpioMotor);
		motor2.Init(GpioMotor);
		motor3.Init(GpioMotor);
		motor4.Init(GpioMotor);
		motor_pwm.Init(rcc.GetPClk1TimerFreq(), MotorConfig);
		motor_pwm.Set({0, 0, 0, 0});

		Board::Printf("    Initialized\r\n");

		//Print clocks
		RccClocks clocks = {};
		rcc.GetSystemClocksFreq(clocks);
		Board::Printf("-SysClkFreq: %d\r\n", clocks.SysClkFreq);
		Board::Printf("-HClkFreq: %d\r\n", clocks.HClkFreq);
		Board::Printf("-PClk1Freq: %d\r\n", clocks.PClk1Freq);
		Board::Printf("-PClk1TimerFreq: %d\r\n", clocks.PClk1TimerFreq);
		Board::Printf("-PClk2Freq: %d\r\n", clocks.PClk2Freq);
	}

	void Write(const ReadOnlyBuffer& buffer)
	{
		SEGGER_RTT_Write(0, buffer.Data, buffer.Length);
	}

	uint32_t GetSysClkFreq()
	{
		return rcc.GetSysClkFreq();
	}
}

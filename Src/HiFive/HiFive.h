#pragma once

namespace HiFive
{
	enum Interrupts
	{
		UserSoftwareInterrupt,
		SupervisorSoftwareInterrupt,
		Reserved0,
		MachineSoftwareInterrupt,
		UserTimerInterrupt,
		SupervisorTimerInterrupt,
		Reserved1,
		MachineTimerInterrupt,
		UserExternalInterrupt,
		SupervisorExternalInterrupt,
		Reserved2,
		MachineExternalInterrupt,
	};

	enum Exceptions
	{
		InstructionAddressMisaligned,
		InstructionAccessFault,
		IllegalInstruction,
		Breakpoint,
		LoadAddressMisaligned,
		LoadAccessFault,
		StoreAddressMisaligned,
		StoreAccessFault,
		EnvironmentCallFromUMode,
		EnvironmentCallFromSMode,
		Reserved3,
		EnvironmentCallFromMMode,
		InstructionPageFault,
		LoadPageFault,
		Reserved4,
		StorePageFault,
	};
}
#include <RiscV.h>
#include <cstdint>

namespace RiscV
{
	uint32_t ReadMIE()
	{
		uint32_t mie = 0;
		asm volatile("csrr %0, mie" : "=r"(mie));
		return mie;
	}

	void WriteMIE(uint32_t mie)
	{
		asm volatile("csrw mie, %0" ::"r"(mie));
	}

	uintptr_t ReadMStatus()
	{
		uintptr_t mstatus = 0;
		asm volatile("csrr %0, mstatus" : "=r"(mstatus));
		return mstatus;
	}

	void WriteMStatus(uintptr_t mstatus)
	{
		asm volatile("csrw mstatus, %0" ::"r"(mstatus));
	}

	uint32_t ReadMtvec()
	{
		uint32_t mtvec = 0;
		asm volatile("csrr %0, mtvec" : "=r"(mtvec));
		return mtvec;
	}

	void WriteMtvec(uint32_t mtvec)
	{
		asm volatile("csrw mtvec, %0" ::"r"(mtvec));
	}

	uint32_t ReadMCause()
	{
		uint32_t mcause = 0;
		asm volatile("csrr %0, mcause" : "=r"(mcause));
		return mcause;
	}

	uint32_t ReadMepc()
	{
		uint32_t mepc = 0;
		asm volatile("csrr %0, mepc" : "=r"(mepc));
		return mepc;
	}

	void WriteMepc(uint32_t mepc)
	{
		asm volatile("csrw mepc, %0" ::"r"(mepc));
	}

	void WriteMip(uint32_t mip)
	{
		asm volatile("csrw mip, %0" ::"r"(mip));
	}

	uint32_t ReadMip()
	{
		uint32_t mip = 0;
		asm volatile("csrr %0, mip" : "=r"(mip));
		return mip;
	}
}
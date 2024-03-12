#pragma once

#include <cstdint>

extern uint32_t __global_pointer$;

namespace RiscV
{
	struct Context
	{
		uint32_t PC;
		uint32_t x1;//RA
		uint32_t x2;//SP
		uint32_t x3;//GP
		uint32_t x4;//TP
		uint32_t x5;
		uint32_t x6;
		uint32_t x7;
		uint32_t x8;
		uint32_t x9;
		uint32_t x10;
		uint32_t x11;
		uint32_t x12;
		uint32_t x13;
		uint32_t x14;
		uint32_t x15;
		uint32_t x16;
		uint32_t x17;
		uint32_t x18;
		uint32_t x19;
		uint32_t x20;
		uint32_t x21;
		uint32_t x22;
		uint32_t x23;
		uint32_t x24;
		uint32_t x25;
		uint32_t x26;
		uint32_t x27;
		uint32_t x28;
		uint32_t x29;
		uint32_t x30;
		uint32_t x31;

		Context(void* entry, void* Idle) :
			PC((uint32_t)entry),
			x1((uint32_t)Idle),
			//x1((uint32_t)entry),
			x2(),
			x3(),
			x4(),
			x5(),
			x6(),
			x7(),
			x8(),
			x9(),
			x10(),
			x11(),
			x12(),
			x13(),
			x14(),
			x15(),
			x16(),
			x17(),
			x18(),
			x19(),
			x20(),
			x21(),
			x22(),
			x23(),
			x24(),
			x25(),
			x26(),
			x27(),
			x28(),
			x29(),
			x30(),
			x31()
		{
		}
	};

	struct MSTATUS
	{
		union
		{
			struct
			{
				uint32_t UIE : 1; 			//User Interrupt Enable
				uint32_t SIE : 1; 			//Supervisor Interrupt Enable
				uint32_t Reserved0 : 1; 	//Reserved
				uint32_t MIE : 1; 			//Machine Interrupt Enable
				uint32_t UPIE : 1; 			//User Previous Interrupt Enable
				uint32_t SPIE : 1; 			//Supervisor Previous Interrupt Enable
				uint32_t Reserved1 : 1; 	//Reserved
				uint32_t MPIE : 1; 			//Machine Previous Interrupt Enable
				uint32_t SPP : 1; 			//Supervisor Previous Privilege
				uint32_t Reserved2 : 2; 	//Reserved
				uint32_t MPP : 2; 			//Machine Previous Privilege
				uint32_t FS : 2; 			//Floating-Point Status
				uint32_t XS : 2; 			//User Extension Status
				uint32_t MPRV : 1; 			//Modify Privilege
				uint32_t SUM : 1; 			//Supervisor User Memory
				uint32_t MXR : 1; 			//Make Executable Readable
				uint32_t TVM : 1; 			//Trap Virtual Memory
				uint32_t TW : 1; 			//Timeout Wait
				uint32_t TSR : 1; 			//Trap SRET
				uint32_t Reserved3 : 8; 	//Reserved
				uint32_t SD : 1; 			//Dirty
			};
			uint32_t AsUint32;
		};
	};
	static_assert(sizeof(MSTATUS) == sizeof(uint32_t), "MSTATUS is not 32 bits");
	
	struct MIE
	{
		union
		{
			struct
			{
				//Software Interrupt Enable
				uint32_t USIE : 1;
				uint32_t SSIE : 1;
				uint32_t Reserved0 : 1;
				uint32_t MSIE : 1;
				//Timer Interrupt Enable
				uint32_t UTIE : 1;
				uint32_t STIE : 1;
				uint32_t Reserved1 : 1;
				uint32_t MTIE : 1;
				//External Interrupt Enable
				uint32_t UEIE : 1;
				uint32_t SEIE : 1;
				uint32_t Reserved2 : 1;
				uint32_t MEIE : 1;
				uint32_t Reserved3 : 4;
				//Local Interrupt Enable
				uint32_t LIE : 16;
			};
			uint32_t AsUint32;
		};
	};
	static_assert(sizeof(MIE) == sizeof(uint32_t), "MIE is not 32 bits");

	struct MIP
	{
		union
		{
			struct
			{
				//Software Interrupt Pending
				uint32_t USIP : 1;
				uint32_t SSIP : 1;
				uint32_t Reserved0 : 1;
				uint32_t MSIP : 1;
				//Timer Interrupt Pending
				uint32_t UTIP : 1;
				uint32_t STIP : 1;
				uint32_t Reserved1 : 1;
				uint32_t MTIP : 1;
				//External Interrupt Pending
				uint32_t UEIP : 1;
				uint32_t SEIP : 1;
				uint32_t Reserved2 : 1;
				uint32_t MEIP : 1;
				uint32_t Reserved3 : 4;
				//Local Interrupt Pending
				uint32_t LIP : 16;
			};
			uint32_t AsUint32;
		};
	};
	static_assert(sizeof(MIP) == sizeof(uint32_t), "MIP is not 32 bits");

	uint32_t ReadMIE();
	void WriteMIE(uint32_t mie);

	uintptr_t ReadMStatus();
	void WriteMStatus(uintptr_t mstatus);

	uint32_t ReadMtvec();
	void WriteMtvec(uint32_t mtvec);

	uint32_t ReadMCause();
	
	uint32_t ReadMepc();
	void WriteMepc(uint32_t mepc);

	uint32_t ReadMip();
	void WriteMip(uint32_t mip);
}
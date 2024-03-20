#pragma once

#include "Sys/Mdio.h"
#include "Assert.h"
#include <Board.h>

// MAN: DS_LAN8742_00001989A-1534922.pdf

class EthPhy
{
public:
	EthPhy(const uint16_t phyAddr) :
		m_phyAddr(phyAddr)
	{
	}

	void Init()
	{
		// Reset Phy
		Mdio::WriteRegister(m_phyAddr, Registers::BasicControl, 0x8000);
		while (Mdio::ReadRegister(m_phyAddr, Registers::BasicControl) & 0x8000)
			;

		// Enable auto-negotiation, wait for finish
		Mdio::WriteRegister(m_phyAddr, Registers::BasicControl, 0x1000);
		while (!(Mdio::ReadRegister(m_phyAddr, Registers::BasicStatus) & 0x0020))
			;

		Assert(LinkUp());
	}
	
	bool LinkUp()
	{
		BasicStatusReg basicStatus;
		basicStatus.AsUint16 = Mdio::ReadRegister(m_phyAddr, Registers::BasicStatus);
		return basicStatus.LinkStatus;
	}
	
	void Display()
	{
		const uint16_t phyId1 = Mdio::ReadRegister(m_phyAddr, Registers::PhyId1);
		const uint16_t phyId2 = Mdio::ReadRegister(m_phyAddr, Registers::PhyId2);
		Board::Printf("EthPhy: %04X:%04X\r\n", phyId1, phyId2);

		BasicStatusReg basicStatus;
		basicStatus.AsUint16 = Mdio::ReadRegister(m_phyAddr, Registers::BasicStatus);
		Board::Printf("    BasicStatus: %04X\r\n", basicStatus.AsUint16);
		Board::Printf("    Link: %04X\r\n", basicStatus.LinkStatus);
	}

protected:
	// MAN: 4.2 Control and Status Registers (CSR)
	enum Registers
	{
		BasicControl,
		BasicStatus,
		PhyId1,
		PhyId2,
	};

	struct __attribute__((packed)) BasicControlReg
	{
		union
		{
			struct
			{
				uint16_t Reserved : 8;
				uint16_t DuplexMode : 1;
				uint16_t RestartAutoNeg : 1;
				uint16_t Isolate : 1;
				uint16_t PowerDown : 1;
				uint16_t AutoNegEnable : 1;
				uint16_t SpeedSelect : 1;
				uint16_t Loopback : 1;
				uint16_t Reset : 1;
			};
			uint16_t AsUint16;
		};
	};
	static_assert(sizeof(BasicControlReg) == sizeof(uint16_t), "Invalid size");

	struct __attribute__((packed)) BasicStatusReg
	{
		union
		{
			struct
			{
				uint16_t ExtendedCaps : 1;
				uint16_t JabberDetect : 1;
				uint16_t LinkStatus : 1;
				uint16_t AutoNegAbility : 1;
				uint16_t RemoteFault : 1;
				uint16_t AutoNegComplete : 1;
				uint16_t Reserved : 2;

				uint16_t ExtendedStatus : 1;
				uint16_t Half_100_T2 : 1;
				uint16_t Full_100_T2 : 1;
				uint16_t Half_10_T : 1;
				uint16_t Full_10_T : 1;
				uint16_t Half_100_TX : 1;
				uint16_t Full_100_TX : 1;
				uint16_t Full_100_T4 : 1;
			};
			uint16_t AsUint16;
		};
	};
	static_assert(sizeof(BasicStatusReg) == sizeof(uint16_t), "Invalid size");

	const uint16_t m_phyAddr;
};

#pragma once

#include "Buffer.h"

//Ref: StSafe Middleware source

//NOTE(tsharpe): MAC not implemented (STSAFEA_USE_OPTIMIZATION_NO_HOST_MAC_ENCRYPT)
namespace Drivers
{
	template <class TChannel>
	class StSafe_A110
	{
	public:
		StSafe_A110(TChannel& channel) :
			m_channel(channel)
		{}

		bool Echo(const ReadOnlyBuffer& buffer)
		{
			const uint8_t header = static_cast<uint8_t>(Cmd::Echo);
			Assert(Write(header, buffer));

			uint8_t receive[buffer.Length + HeaderSize + LengthSize];
			Buffer recBuffer;
			recBuffer.Data = receive;
			recBuffer.Length = sizeof(receive);
			
			Assert(Read(recBuffer));
			return true;
		}

	private:
		static constexpr uint8_t Address = 0x20;
		static constexpr size_t HeaderSize = sizeof(uint8_t);
		static constexpr size_t LengthSize = sizeof(uint16_t);
		static constexpr size_t CrcSize = sizeof(uint16_t);

		//REF: StSafeA_Transmit
		bool Write(const uint8_t header, const ReadOnlyBuffer& buffer)
		{
			//NOTE(tsharpe): CRCs not supported

			uint8_t transmit[buffer.Length + HeaderSize + CrcSize];
			transmit[0] = header;
			memcpy(&transmit[HeaderSize], buffer.Data, buffer.Length);

			return m_channel.Write(Address, {transmit, sizeof(transmit)});
		}

		bool Read(const Buffer& buffer)
		{
			return m_channel.Read(Address, buffer);
		}

		enum class Cmd : uint8_t
		{
			Echo = 0x00,
			Reset = 0x01,
			GenerateRandom = 0x02,
			StartSession = 0x03,
			Decrement = 0x04,
			Read = 0x05,
			Update = 0x06,
			DeleteKey = 0x0C,
			Hibernate = 0x0D,
			WrapLocalEnvelope = 0x0F,
			PutAttribute = 0x10,
			GenerateKey = 0x11,
			Query = 0x14,
			GenerateSignature = 0x16,
			VerifySignature = 0x17,
			EstablishKey = 0x18,
			VerifyPassword = 0x1A
		};

		TChannel& m_channel;
	};
}
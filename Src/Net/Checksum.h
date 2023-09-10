#include <cstdint>
#include <cstring>
#include <cstddef>

namespace Net
{
	//http://www.faqs.org/rfcs/rfc1071.html Section 4.1
	//http://www.microhowto.info/howto/calculate_an_internet_protocol_checksum_in_c.html
	//Input and output in network byte order (big-endian)
	class Checksum
	{
	public:
		static uint16_t Compute(const void* vdata, const size_t length)
		{
			Checksum checksum;
			checksum.Add(vdata, length);
			return checksum.Get();
		}

		Checksum() :
			m_accumulator(0xFFFF)
		{

		}

		void Add(const void* vdata, const size_t length)
		{
			// Cast the data pointer to one that can be indexed.
			char* data = (char*)vdata;
			
			// Handle complete 16-bit blocks.
			for (size_t i = 0; i + 1 < length; i += 2) {
				uint16_t word;
				memcpy(&word, data + i, 2);
				m_accumulator += word;
				if (m_accumulator > 0xffff) {
					m_accumulator -= 0xffff;
				}
			}

			// Handle any partial block at the end of the data.
			if (length & 1) {
				uint16_t word = 0;
				memcpy(&word, data + length - 1, 1);
				m_accumulator += word;
				if (m_accumulator > 0xffff) {
					m_accumulator -= 0xffff;
				}
			}
		}

		void Add(const uint16_t value)
		{
			m_accumulator += htons(value);
			if (m_accumulator > 0xffff) {
				m_accumulator -= 0xffff;
			}
		}

		uint16_t Get()
		{
			return ~m_accumulator;
		}

	private:
		uint32_t m_accumulator;
	};
}

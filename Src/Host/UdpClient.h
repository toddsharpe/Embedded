#pragma once

#include "Assert.h"
#include "Rtos/Types.h"
#include "Net/Net.h"

#include <arpa/inet.h>
#include <cstdint>
#include <cstddef>
#include <cerrno>
#include <string.h>

#define AssertErrNo(x) \
	if (x == -1) \
	{ \
		Bugcheck("File: " __FILE__, "Line: " STR(__LINE__),  #x " errno = %d", errno); \
	}

namespace Host
{
	class UdpClient
	{
	public:
		UdpClient(const Net::IpAddress& server, const uint16_t port) :
			m_server(server),
			m_port(port),
			m_fd()
		{

		}

		void Init()
		{
			//Create socket
			m_fd = socket(AF_INET, SOCK_DGRAM, 0);
			AssertErrNo(m_fd);
		}

		void Receive(void* buffer, const size_t count)
		{
			struct sockaddr_in src = {};
			socklen_t len = sizeof(src);
			ssize_t bytes = recvfrom(m_fd, buffer, count, MSG_WAITALL, (struct sockaddr *)&src, &len);
			AssertErrNo(bytes);
		}

		void Send(const void* buffer, const size_t count)
		{
			struct sockaddr_in dest = {};
			dest.sin_family = AF_INET;
			dest.sin_addr.s_addr = INADDR_ANY;
			dest.sin_port = htons(m_port);

			int ret = sendto(m_fd, buffer, count, 0, (const struct sockaddr *)&dest, sizeof(dest));
			AssertErrNo(ret);
		}

		template<class TSend, class TReceive>
		void SendAndReceive(TSend& send, TReceive& receive)
		{
			Send(&send, sizeof(send));
			Receive(&receive, sizeof(receive));
		}

	private:
		const Net::IpAddress& m_server;
		const uint16_t m_port;
		int m_fd;
	};
}

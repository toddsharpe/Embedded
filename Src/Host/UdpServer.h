#pragma once

#include "Assert.h"

#include <arpa/inet.h>
#include <cstdint>
#include <cstddef>
#include <cerrno>
#include <cstdio>

#define AssertErrNo(x) \
	if (x == -1) \
	{ \
		Bugcheck("File: " __FILE__, "Line: " STR(__LINE__),  #x " errno = %d", errno); \
	}

namespace Host
{
	class UdpServer
	{
	public:
		UdpServer(const uint16_t port) :
			m_port(port),
			m_fd(),
			m_client()
		{

		}

		void Init()
		{
			//Create socket
			m_fd = socket(AF_INET, SOCK_DGRAM, 0);
			AssertErrNo(m_fd);

			//Bind
			struct sockaddr_in addr = {};
			addr.sin_family = AF_INET;
			addr.sin_addr.s_addr = htonl(INADDR_ANY);
			addr.sin_port = htons(m_port);
			int ret = bind(m_fd, (struct sockaddr *)&addr, sizeof(addr));
			AssertErrNo(ret);
		}

		size_t Receive(void* buffer, const size_t count)
		{
			socklen_t len = sizeof(m_client);
			ssize_t bytes = recvfrom(m_fd, buffer, count, MSG_WAITALL, (struct sockaddr *)&m_client, &len);
			printf("Received %ld bytes from %s:%d\n", bytes, inet_ntoa(m_client.sin_addr), ntohs(m_client.sin_port));
			AssertErrNo(bytes);
			return bytes;
		}

		void Send(const void* buffer, const size_t count)
		{
			socklen_t len = sizeof(m_client);
			int ret = sendto(m_fd, buffer, count, 0, (const struct sockaddr *)&m_client, len);
			AssertErrNo(ret);
			Assert(ret == count);
		}

	private:
		const uint16_t m_port;
		int m_fd;
		struct sockaddr_in m_client;
	};
}

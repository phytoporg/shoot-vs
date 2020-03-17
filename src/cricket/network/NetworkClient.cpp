#include "NetworkClient.h"

#include <utility/FailFast.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

namespace cricket
{
    NetworkClient::NetworkClient()
    {
        m_sockFd = socket(AF_INET, SOCK_STREAM, 0);

        //
        // Experimenting with exceptionless design. This doesn't... seem like
        // the right approach, but it'll do for now.
        //
        if (m_sockFd < 0) { FailFast(); }
    }

    bool NetworkClient::Connect(const std::string& host, uint16_t port) 
    {
        if (m_connected) { return true; }

        struct sockaddr_in serv_addr; 
		serv_addr.sin_family = AF_INET; 
		serv_addr.sin_port = htons(port); 
		   
		// Convert IPv4 and IPv6 addresses from text to binary form 
		if(inet_pton(AF_INET, host.c_str(), &serv_addr.sin_addr) <= 0)  
		{ 
			return false; 
		} 

		if (connect(
            m_sockFd,
            reinterpret_cast<struct sockaddr *>(&serv_addr), 
            sizeof(serv_addr)) < 0) 
		{ 
			return false; 
		} 

        m_connected = true;
        return true; 
    }

    void NetworkClient::Disconnect() 
    {
        close(m_sockFd);
        m_connected = false;
        m_sockFd = 0;
    }

    size_t NetworkClient::Send(const std::vector<uint8_t>& data)
    {
        return Send(data.data(), data.size());
    }

    size_t NetworkClient::Send(uint8_t const* pData, size_t payloadSize)
    {
        if (!m_connected) { return 0; }

        const int Flags{0};
        const auto BytesSent = 
            send(m_sockFd, pData, payloadSize, Flags);
        if (BytesSent < 0)
        {
            return 0;
        }

        return BytesSent;
    }

    size_t NetworkClient::Receive(
        std::vector<uint8_t>* pData,
        size_t startIndex)
    {
        //
        // TODO
        //
        return 0;
    }
    
    size_t NetworkClient::Receive(uint8_t* pBuffer, size_t maxBufferSize)
    {
        //
        // TODO
        //
        return 0;
    }
}

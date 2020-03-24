#include "NetworkClient.h"

#include <utility/FailFast.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <cassert>

namespace cricket
{
    NetworkClientPtr NetworkClient::MakeAndInitialize()
    {
        NetworkClientPtr spClient;
        int sockFd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockFd < 0) { return spClient; }

        spClient.reset(new NetworkClient(sockFd));
    }

    NetworkClient::NetworkClient(int socket)
        : m_sockFd(socket), m_connected{false}
    {}

    NetworkClient::~NetworkClient()
    {
        Disconnect();

        close(m_sockFd);
        m_connected = false;
        m_sockFd = 0;
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
        shutdown(m_sockFd, 2);
    }

    size_t NetworkClient::Send(const std::vector<uint8_t>& data)
    {
        return Send(data.data(), data.size());
    }

    size_t NetworkClient::Send(uint8_t const* pData, size_t payloadSize)
    {
        assert(pData);
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
        assert(pData);
        if (!m_connected)                { return 0; }
        if (startIndex >= pData->size()) { return 0; }

        const size_t MaxBufferSize{startIndex - pData->size()};
        return Receive(pData->data() + startIndex, MaxBufferSize);
    }
    
    size_t NetworkClient::Receive(uint8_t* pBuffer, size_t maxBufferSize)
    {
        assert(pBuffer);
        if (!m_connected) { return 0; } // Hrm. Could check this twice :(

        const int Flags{0};
        return recv(m_sockFd, pBuffer, maxBufferSize, Flags);
    }
}


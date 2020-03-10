//
// A network client helper class!
//
#pragma once

#include <string>
#include <vector>

namespace cricket
{
    class NetworkClient
    {
    public:
        NetworkClient();
        virtual ~NetworkClient() = default;

        bool Connect(const std::string& host, uint16_t port);
        void Disconnect();

        //
        // Returns the number of bytes sent, or zero on failure. These are 
        // blocking calls.
        //
        size_t Send(const std::vector<uint8_t>& data);
        size_t Send(uint8_t const* pData, size_t payloadSize);

        //
        // Returns the number of bytes received, or zero on failure.
        //
        size_t Receive(std::vector<uint8_t>* pData, size_t startIndex = 0);
        size_t Receive(uint8_t* pBuffer, size_t maxBufferSize);

    private:
        int  m_sockFd;
        bool m_connected;
    };
}


#include "NetworkServerListener.h"

#include <chrono>
#include <cstring>
#include <thread>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <fcntl.h>
#include <unistd.h>

namespace cricket
{
    NetworkServerListenerPtr NetworkServerListener::MakeAndInitialize(
        ClientCallbackType& callback)
    {
        NetworkServerListenerPtr spServerPtr;
        spServerPtr.reset(new NetworkServerListener(callback));

        return spServerPtr;
    }

    NetworkServerListener::NetworkServerListener(ClientCallbackType& callback)
        : m_callbackFn(callback), m_accepting(true)
    {}

    NetworkServerListener::~NetworkServerListener()
    {
        if (m_socket) { close(m_socket); }
        StopListening();
    }

    bool NetworkServerListener::ListenForConnections(int port)
    {
        const int ServerSock = socket(AF_INET, SOCK_STREAM, 0);
        if (ServerSock < 0) { return false; }
        m_socket = ServerSock;

        //
        // ServerSock -> nonblocking socket.
        //
        const int Flags{fcntl(ServerSock, F_GETFL)};
        if (Flags < 0) { return false; }

        if (fcntl(ServerSock, F_SETFL, Flags | O_NONBLOCK) < 0)
        { return false; }

        int enable = 1;
        if (setsockopt(
            m_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        { return false; }

        m_port = port;
        struct sockaddr_in servaddr;
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family      = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port        = htons(m_port);

        if (bind(m_socket, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        {
            m_socket = 0;
            m_port = 0;
            return false;
        }

        const int ListenQ{1024};
        if (listen(ServerSock, ListenQ) < 0)
        {
            m_socket = 0;
            m_port = 0;
            return false;
        }

        while (m_accepting)
        {
            const int Connection = accept(m_socket, nullptr, nullptr);
            if (Connection < 0)
            {
                if (errno == EWOULDBLOCK)
                {
                    //
                    // No pending connections. Sleep and try again.
                    //
                    using namespace std::chrono_literals;
                    const auto SleepDuration{500ms};
                    std::this_thread::sleep_for(SleepDuration);
                }
                else
                {
                    m_accepting = false;
                }
            }
            else
            {
                m_callbackFn(NetworkClient::MakeAndInitialize(Connection));
            }
        }

        return true;
    }

    void NetworkServerListener::StopListening()
    {
        m_accepting = false;
    }
}


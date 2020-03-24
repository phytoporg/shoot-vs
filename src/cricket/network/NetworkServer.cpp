#include "NetworkServer.h"

#include <cstring>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <unistd.h>

namespace cricket
{
    NetworkServerPtr NetworkServer::MakeAndInitialize(
        ClientCallbackType& callback)
    {
        NetworkServerPtr spServerPtr;
        spServerPtr.reset(new NetworkServer(callback));

        return spServerPtr;
    }

    NetworkServer::NetworkServer(ClientCallbackType& callback)
        : m_callbackFn(callback), m_accepting(true)
    {}

    NetworkServer::~NetworkServer()
    {
        if (m_socket) { close(m_socket); }
        m_accepting = false;
    }

    bool NetworkServer::WaitForConnections(int port)
    {
        const int ServerSock = socket(AF_INET, SOCK_STREAM, 0);
        if (ServerSock < 0) { return false; }
        m_socket = ServerSock;

        int enable = 1;
        if (setsockopt(
            m_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        {
            return false;
        }

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
            if (!Connection)
            {
                m_accepting = false;
            }
            else
            {
                m_callbackFn(Connection);
            }
        }
    }
}


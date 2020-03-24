//
//  Network server object. Just TCP for now.
//

#pragma once

#include <functional>
#include <memory>

namespace cricket
{
    class NetworkServer;
    using NetworkServerPtr = std::shared_ptr<NetworkServer>;

    class NetworkServer
    {
    public:
        using ClientCallbackType = std::function<void(int)>;
        static NetworkServerPtr MakeAndInitialize(ClientCallbackType& callback);
        virtual ~NetworkServer();

        bool WaitForConnections(int port);

    private:
        NetworkServer(ClientCallbackType& callback);
        ClientCallbackType& m_callbackFn;

        int m_port;
        int m_socket;
        bool m_accepting;
    };
}


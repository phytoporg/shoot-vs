//
// This object facilitates waiting for and collecting client connections.
//

#pragma once

#include <functional>
#include <memory>

#include "NetworkClient.h"

namespace cricket
{
    class NetworkServerListener;
    using NetworkServerListenerPtr = std::shared_ptr<NetworkServerListener>;

    class NetworkServerListener
    {
    public:
        using ClientCallbackType = std::function<void(NetworkClientPtr)>;
        static NetworkServerListenerPtr 
            MakeAndInitialize(ClientCallbackType& callback);
        virtual ~NetworkServerListener();

        //
        // These two are not thread safe wrt the "currently listening" state.
        // Call from the same thread.
        //
        bool ListenForConnections(int port);
        void StopListening();

    private:
        NetworkServerListener(ClientCallbackType& callback);
        ClientCallbackType& m_callbackFn;

        int m_port;
        int m_socket;
        bool m_accepting;
    };
}


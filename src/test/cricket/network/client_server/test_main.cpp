#include <chrono>
#include <condition_variable>
#include <future>
#include <mutex>
#include <thread>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <gtest/gtest.h>
#include <cricket/network/NetworkClient.h>
#include <cricket/network/NetworkServerListener.h>

using namespace std::chrono_literals;

TEST(ClientServerTest, ClientInstantiation)
{
    auto spClient = cricket::NetworkClient::MakeAndInitialize();
    ASSERT_TRUE(!!spClient);
}

TEST(ClientServerTest, ClientConnect)
{
    auto spClient = cricket::NetworkClient::MakeAndInitialize();
    ASSERT_TRUE(!!spClient);

    const int ServerSock = socket(AF_INET, SOCK_STREAM, 0);
    ASSERT_GE(ServerSock, 0);

    int enable = 1;
    ASSERT_GE(setsockopt(
        ServerSock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)), 0);

    const int PortToUse{1337};
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(PortToUse);

	ASSERT_GE(
		bind(ServerSock, (struct sockaddr *) &servaddr, sizeof(servaddr)),
        0);

    const int ListenQ{1024};
    ASSERT_GE(listen(ServerSock, ListenQ), 0);

    std::mutex mutex;
    std::condition_variable cv;
    bool connected{false};

    auto serverAcceptFuture = std::async(
        std::launch::async,
        [&cv, &connected, &ServerSock]()
        {
            const int Connection{accept(ServerSock, nullptr, nullptr)};
            connected = !!Connection;
            if (connected)
            {
                close(Connection);
            }
            cv.notify_all();
        });

    ASSERT_TRUE(spClient->Connect("127.0.0.1", PortToUse));

    std::unique_lock<std::mutex> lock(mutex);
    ASSERT_TRUE(cv.wait_for(lock, 200ms, [&connected]{ return connected; })); 
}

TEST(ClientServerTest, ServerListenerConnect)
{
    bool callbackInvoked = false;
    std::condition_variable cv;
    cricket::NetworkServerListener::ClientCallbackType 
        clientConnectionCallback = [&cv, &callbackInvoked](
                cricket::NetworkClientPtr spClient
            )
        {
            ASSERT_TRUE(!!spClient);

            callbackInvoked = true;
            cv.notify_all();
        };
    auto spServerListener = 
        cricket::NetworkServerListener::MakeAndInitialize(
            clientConnectionCallback);
    auto spClient = 
        cricket::NetworkClient::MakeAndInitialize();

    const int PortToUse{1338};
    std::thread listenerThread([&PortToUse, &spServerListener](){
            ASSERT_TRUE(spServerListener->ListenForConnections(PortToUse));
        });

    std::this_thread::sleep_for(50ms);
    spClient->Connect("127.0.0.1", PortToUse);

    std::mutex mutex;
    std::unique_lock<std::mutex> lock(mutex);
    ASSERT_TRUE(
        cv.wait_for(
            lock, 500ms, [&callbackInvoked](){ return callbackInvoked; }));

    spServerListener->StopListening();
    listenerThread.join();
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


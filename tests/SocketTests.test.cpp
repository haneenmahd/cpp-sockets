#include <iostream>
#include "Socket.h"
#include "TestEssentials.h"

int main()
{
    // client testing
    SocketClient client(3000, "Test Client");

    expect_int("Expect state to be initialised", client.state, 3);

    client.setAddressConfiguration();

    expect_int("Expect state to be initialised", client.state, 3);

    // server testing
    Socket serv(3000, "Test Server");

    expect_int("Expect the state to be uninitialised", serv.state, 2);

    serv.initSocket();

    expect_int("Expect the state to be initialised", serv.state, 3);

    serv.attachToPort();

    expect_int("Expect the state to be initialised", serv.state, 2);

    serv.setAddressConfiguration();

    expect_int("Expect the state to be initialised", serv.state, 2);

    serv.bindSocket();

    expect_int("Expect the state to be initialised", serv.state, 2);

    serv.listenSocket();

    expect_int("Expect the state to be alive", serv.state, 1);

    return 0;
}
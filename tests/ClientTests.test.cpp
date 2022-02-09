#include <iostream>
#include "Socket.h"
#include "TestEssentials.h"

int main()
{
    SocketClient client(3000, "Test Client");

    expect_int("Expect state to be initialised", client.state, 3);

    client.setAddressConfiguration();

    expect_int("Expect state to be initialised", client.state, 3);

    return 0;
}
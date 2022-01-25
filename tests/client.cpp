#include <iostream>
#include "socket/SocketClient.h"

int main()
{
    SocketClient socket(8080, "Hello World");

    socket.setAddressConfiguration();
    socket.connectSocket();
    return 0;
}
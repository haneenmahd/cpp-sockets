#define DEBUG
#include <iostream>
#include "Socket.h"

int main()
{
    SocketClient socket(3031, "Hello World");

    socket.setAddressConfiguration();
    socket.connectSocket();
    return 0;
}
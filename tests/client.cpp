#define DEBUG
#include <iostream>
#include "Socket.h"

int main()
{
    SocketClient socket(3031, "Hello World from client");

    socket.setAddressConfiguration();
    socket.connectSocket();
    return 0;
}
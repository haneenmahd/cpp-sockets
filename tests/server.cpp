#define DEBUG
#include <iostream>
#include "Socket.h"

int main()
{
    Socket socket(3031, "Hello World");

    socket.initSocket();

    socket.attachToPort();
    socket.setAddressConfiguration();
    socket.bindSocket();

    socket.listenSocket();
    socket.acceptNewSocket();
    sleep(1);

    return 0;
}
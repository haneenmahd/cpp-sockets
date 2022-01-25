#include <iostream>
#include "Socket.h"

int main()
{
    Socket socket(8080, "Hello World");

    socket.initSocket();

    socket.attachToPort();
    socket.setAddressConfiguration();
    socket.bindSocket();

    socket.listenSocket();
    socket.acceptNewSocket();

    return 0;
}
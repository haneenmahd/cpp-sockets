#define DEBUG
#include <iostream>
#include "Socket.h"

int main()
{
    Socket socket(3031, "Hello World from server");

    socket.initSocket();
    socket.attachToPort();
    socket.setAddressConfiguration();
    socket.bindSocket();
    socket.listenSocket();
    std::cout << "Buffer from accept: " << socket.acceptNewSocket() << std::endl;

    return 0;
}
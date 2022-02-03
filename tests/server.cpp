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
    socket.acceptNewSocket();
    std::cout << socket.getMessage() << std::endl;
    socket.sendMessage();

    return 0;
}
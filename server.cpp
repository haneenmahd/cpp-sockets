#include <iostream>
#include "socket/Socket.h"

int main()
{
    Socket socket(8080, "Hello World");

    socket.listenSocket();
    socket.acceptNewSocket();
    return 0;
}
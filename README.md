# cpp-sockets
Object Oriented Implementation of Unix Sockets

# Usage
There are 2 Main Objects defined in this package.
- `Socket` used for defining server side sockets
- `SocketClient` used for creating client side sockets

Here is a sample code to fire up a socket in server side.
```cpp
#include "Socket.h"

int main()
{
    Socket serv(8080 /* PORT */, "Hello World" /* Response to send */);

    serve.initSocket(); // initialize socket

    socket.attachToPort(); // attaches to the port specificied
    socket.setAddressConfiguration(); // creates a address structure and configures it

    socket.bindSocket(); // binds socket to the port

    socket.listenSocket(); // listens for socket on the port specified
    socket.acceptNewSocket(); // accepts new connections

    return 0;
}
```

Example Client side
```cpp
#include "SocketClient.h"

int main()
{
    SocketClient socket(3031, "Hello World");

    socket.setAddressConfiguration(); // setup the address configuration
    socket.connectSocket(); // connects to the socket
    return 0;
}
```
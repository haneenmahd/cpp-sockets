# cpp-sockets 👽
Object Oriented Implementation of Unix Sockets

# Installataion
Download and move the `Socket.h` to your project's include directory.

You are ready to go 🚀!

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
    socket.acceptNewSocket(); // accepts new connections and returns the message for the current connection

    return 0;
}
```

Example Client side
```cpp
#include "Socket.h"

int main()
{
    SocketClient socket(3031, "Hello World");

    socket.setAddressConfiguration(); // setup the address configuration
    socket.connectSocket(); // connects to the socket
    return 0;
}
```

## Socket Functions 🥶
- **`initSocket`**
    - `returnValue`: is a void function, does not return anything
    - `Functionality`: Initialises the socket using the `socket` function defined in `socket.h`
- **`attachToPort`**
    - `returnValue`: is a void function, does not return anything
    - `Functionality`: Attaches the socket to port
- **`setAddressConfiguration`**
    - `returnValue`: is a void function, does not return anything
    - `Functionality`: sets the address value structure of the socket, uses `sockaddr`
- **`bindSocket`**
    - `returnValue`: is a void function, does not return anything
    - `Functionality`: Binds socket to the port
- **`listenSocket`**
    - `returnValue`: is a void function, does not return anything
    - `Functionality`: listens on the port specifed
- **`acceptNewSocket`**
    - `returnValue`: returns a string
    - `Functionality`: accepts new connections on the port and returns the message recieved in each connection.
- **`sendMessage`**
    - `returnValue`: typeof _SocketStatus_, a enum with cases FAILED = 0, SUCCESS = 1
    - `Functionality`: sends the message specified in the constructor to the any available connections
- **`stayAlive`**
    - `returnValue`: is a void function, does not return anything
    - `Functionality`: makes the socket alive forever, uses **acceptNewSocket**
- **`connectSocket`**
    - `returnValue`: is a void function, does not return anything
    - `Functionality`: Connects the socket to the specified port

## License
`cpp-sockets` is an open-source project licensed under MIT.

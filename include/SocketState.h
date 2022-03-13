/**
 * Socket state is defined to debug any errors inside the socket, and it emits the state of the socket
 * These are the defenitions of specific cases that will occur inisde socket status.
 * 0 - ALIVE - The socket is live on a specific port, without any errors
 * 1 - DEAD - The socket is killed or terminated by the process
 * 2 - UNINITALISED - The socket is not initialized or attached or binded to a specific port
 * 3 - INITIALISED - The socket is attached or binded to a specific port
 **/
typedef enum
{
    ALIVE,
    DEAD,
    UNINITIALIZED,
    INITIALISED
} SocketState;
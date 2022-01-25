#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

// the objected-oriented implementation of socket programming
class Socket
{
private:
    int PORT;
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt;
    int addrlen;
    char buffer[1024];
    const char* message;

    // attaches to the port specified in the paramters
    void attachToPort();

    // set address configuration
    void setAddressConfiguration();

    // bind socket
    void bindSocket();
public:
    Socket(int _PORT, const char* message);

    // starts listening on the port specified
    void listenSocket();

    // accept new socket connections
    void acceptNewSocket();
};

Socket::Socket(int _PORT, const char* _message)
{
    PORT = _PORT;
    message = _message;

    // setting default values
    opt = 1;
    addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        #ifdef DEBUG
            printf("Failed to create socket, occured in file: %s, line: %d\n", __FILE__, __LINE__);
        #endif
        exit(EXIT_FAILURE);
    }

    attachToPort();
    setAddressConfiguration();
    bindSocket();
}

void Socket::attachToPort() 
{
    if ((setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))))
    {
        #ifdef DEBUG
            printf("Failed to bind socket to port: %d, occured in file: %s, line: %d\n", PORT, __FILE__, __LINE__);
        #endif
        exit(EXIT_FAILURE);
    }
}

void Socket::setAddressConfiguration()
{
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
}

void Socket::bindSocket()
{
    if ((bind(server_fd, (struct sockaddr *)&address, sizeof(address))) < 0)
    {
        #ifdef DEBUG
            printf("Failed to bind socket on port: %d, occured in file: %s, line: %d\n", PORT, __FILE__, __LINE__);
        #endif
        exit(EXIT_FAILURE);
    }
}

void Socket::listenSocket()
{
    if (listen(server_fd, 3) < 0)
    {
        #ifdef DEBUG
            printf("Failed to listen on port: %d, occured in file: %s, line: %d\n", PORT, __FILE__, __LINE__);
        #endif
        exit(EXIT_FAILURE);
    }
}

void Socket::acceptNewSocket()
{
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
    {
        #ifdef DEBUG
            printf("Failed to accept new socket connections on port: %d, occured in file: %s, line: %d\n", PORT, __FILE__, __LINE__);
        #endif
        exit(EXIT_FAILURE);
    }
    
    valread = read(new_socket, buffer, 1024);
    printf("buffer recieved: %s", buffer);

    send(new_socket, message, strlen(message), 0);
    #ifdef DEBUG
        printf("Message Sent!");
    #endif
}
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string>

// the objected-oriented implementation of socket programming
class Socket
{
private:
    int PORT;
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt;
    int addrlen;
    std::string buffer;
    std::string message;
public:
    // socket initializer
    Socket(int _PORT, std::string message);

    // init socket
    int initSocket(int addressFamily = AF_INET, int socketType = SOCK_STREAM);

    // attaches to the port specified in the paramters
    void attachToPort();

    // set address configuration
    void setAddressConfiguration(int addressFamily = AF_INET, uint32_t sAddr = INADDR_ANY);

    // bind socket
    void bindSocket();

    // starts listening on the port specified
    void listenSocket();

    // accept new socket connections
    void acceptNewSocket();
};

Socket::Socket(int _PORT, std::string _message)
{
    PORT = _PORT;
    message = _message;

    // setting default values
    opt = 1;
    addrlen = sizeof(address);
}

int Socket::initSocket(int addressFamily, int socketType)
{
    if ((server_fd = socket(addressFamily, socketType, 0)) == 0)
    {
#ifdef DEBUG
        printf("Failed to create socket, occured in file: %s, line: %d\n", __FILE__, __LINE__);
#endif
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void Socket::attachToPort() 
{
    if ((setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))))
    {
        #ifdef DEBUG
            printf("Failed to attach socket to port: %d, occured in file: %s, line: %d\n", PORT, __FILE__, __LINE__);
        #endif
        exit(EXIT_FAILURE);
    }
}

void Socket::setAddressConfiguration(int addressFamily, uint32_t sAddr)
{
    address.sin_family = addressFamily;
    address.sin_addr.s_addr = sAddr;
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
    
    valread = read(new_socket, (void*)buffer.c_str(), 1024);
    printf("buffer recieved: %s\n", buffer.c_str());

    send(new_socket, message.c_str(), message.length(), 0);

    #ifdef DEBUG
        printf("Message Sent!");
    #endif
}
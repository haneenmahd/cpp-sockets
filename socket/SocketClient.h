#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

class SocketClient
{
private:
    int PORT;
    int sock, valread;
    struct sockaddr_in serv_addr;
    const char* message;
    char buffer[1024];
public:
    SocketClient(int _PORT, const char* _message);

    // setup the address configuration structure
    void setAddressConfiguration();
    // connect
    void connectSocket();
};

SocketClient::SocketClient(int _PORT, const char* _message)
{
    PORT = _PORT;
    message = _message;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Client Side Socket creation failed. \n");
        exit(EXIT_FAILURE);
    }
}

void SocketClient::setAddressConfiguration()
{
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address || Address not supported \n");
        exit(EXIT_FAILURE);
    }
}

void SocketClient::connectSocket() {
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))
    {
        printf("\n Connection Failed \n");
        exit(EXIT_FAILURE);
    }
    
    send(sock, message, strlen(message), 0);

    printf("Message sent\n");
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);
}
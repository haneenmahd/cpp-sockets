#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>

typedef enum
{
    ALIVE,
    DEAD,
    UNINITIALIZED,
    INITIALISED
} SocketStatus;

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
    SocketStatus status;

    // socket initializer
    Socket(int _PORT, std::string _message) {
        PORT = _PORT;
        message = _message;

        // setting default values
        opt = 1;
        addrlen = sizeof(address);

        // set deafault value
        status = UNINITIALIZED;
    };

    // init socket
    int initSocket(int addressFamily = AF_INET, int socketType = SOCK_STREAM)
    {
        if ((server_fd = socket(addressFamily, socketType, 0)) == 0)
        {
            std::cout << "Failed to create socket, occured in file: " << __FILE__ << ", line: " << __LINE__ << std::endl;
            return EXIT_FAILURE;
        }

        // set socket status
        status = INITIALISED;

        return EXIT_SUCCESS;
    }

    // attaches to the port specified in the paramters
    void attachToPort()
    {
        if ((setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))))
        {
            std::cout << "Failed to attach socket to port" << PORT << ", occured in file: " << __FILE__ << ", line: " << __LINE__ << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    // set address configuration
    void setAddressConfiguration(int addressFamily = AF_INET, uint32_t sAddr = INADDR_ANY)
    {
        address.sin_family = addressFamily;
        address.sin_addr.s_addr = sAddr;
        address.sin_port = htons(PORT);
    }

    // bind socket
    void bindSocket()
    {
        if ((bind(server_fd, (struct sockaddr *)&address, sizeof(address))) < 0)
        {
            printf("Failed to bind socket on port: %d, occured in file: %s, line: %d\n", PORT, __FILE__, __LINE__);
            exit(EXIT_FAILURE);
        }
    }

    // starts listening on the port specified
    void listenSocket()
    {
        if (listen(server_fd, 3) < 0)
        {
            std::cout << "Failed to listen socket to port" << PORT << ", occured in file: " << __FILE__ << ", line: " << __LINE__ << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    // accept new socket connections
    void acceptNewSocket()
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            std::cout << "Failed to accept new socket to port" << PORT << ", occured in file: " << __FILE__ << ", line: " << __LINE__ << std::endl;
            exit(EXIT_FAILURE);
        }

        // set socket status
        status = ALIVE;

        valread = read(new_socket, (void *)buffer.c_str(), 1024);
        std::cout << "Buffer recieved: " << buffer.c_str() << std::endl;

        send(new_socket, message.c_str(), message.length(), 0);

        std::cout << "Message Sent: " << &buffer << std::endl;
    }

    /**
     * @brief Starts up the server and stays alive forever until the program is then finally terminated
     * 
     */
    void stayAlive() {
        while (true)
        {
            this->acceptNewSocket();
        }

        // set socket status
        status = DEAD; // socket is always dead after the termination of the forever loop
    }
};

// Object oriented implementation of Client-Side Socket
class SocketClient
{
private:
    int PORT;
    int sock, valread;
    struct sockaddr_in serv_addr;
    std::string buffer;
    std::string message;

public:
    SocketClient(int _PORT, std::string _message)
    {
        PORT = _PORT;
        message = _message;

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Client Side Socket creation failed. \n");
            exit(EXIT_FAILURE);
        }
    }

    // setup the address configuration structure
    void setAddressConfiguration()
    {
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
        {
            printf("\nInvalid address || Address not supported \n");
            exit(EXIT_FAILURE);
        }
    }
    // connect
    void connectSocket()
    {
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)))
        {
            printf("\n Connection Failed \n");
            exit(EXIT_FAILURE);
        }

        send(sock, message.c_str(), message.length(), 0);

        printf("Message sent\n");
        valread = read(sock, (void *)buffer.c_str(), 1024);
        printf("%s\n", buffer.c_str());
    }
};
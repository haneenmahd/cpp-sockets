/**
 * @file Socket.h
 * @author Haneen Mahdin (haneenmahdin@gmail.com)
 * @brief Main Definition for OOP-implementation of Socket functions 
 * @version 1.0
 * @date 2022-02-07
 * 
 * @copyright Copyright (c) 2022 Haneen Mahdin
 * 
 */

#define CPP_SOCKETS_H

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include  "SocketState.h"
#include "SocketStatus.h"

/**
     * @brief Construct a new Socket object
     * Warning ⚠️: This does not initialize a socket, you need to do it manually by calling .initSocket() on your Socket object.
     * @param _PORT port to host the server, this port should be used by the client in-order to connect to this specific socket
     * @param _message Message the client will recieve
     */
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
    SocketState state;

    /**
     * @brief Construct a new Socket object
     * Warning ⚠️: This does not initialize a socket, you need to do it manually by calling `.initSocket()` on your Socket object.
     * @param _PORT port to host the server, this port should be used by the client in-order to connect to this specific socket
     * @param _message Message the client will recieve
     */
    Socket(int _PORT, std::string _message)
    {
        PORT = _PORT;
        message = _message;

        // setting default values
        opt = 1;
        addrlen = sizeof(address);

        // set deafault value
        state = UNINITIALIZED;
    };

    /**
     * @brief Initializes the socket, sets the address family and socket type
     * 
     * @param addressFamily The Address Family that the socket should use
     * @param socketType The type of socket, most used: SOCK_STREAM, SOCK_DGRAM, SOCK_RAW
     * @return int 
     */
    SocketStatus initSocket(int addressFamily = AF_INET, int socketType = SOCK_STREAM)
    {
        if ((server_fd = socket(addressFamily, socketType, 0)) == 0)
        {
            std::cout << "Failed to create socket, occured in file: " << __FILE__ << ", line: " << __LINE__ << std::endl;
            return FAILED;
        }

        // set socket status
        state = INITIALISED;

        return SUCCESS;
    }

    /**
     * @brief Attaches a socket to the port specified in the constructor
     * Uses SOL_SOCKET, SO_REUSEADDR
     */
    SocketStatus attachToPort()
    {
        if ((setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))))
        {
            std::cout << "Failed to attach socket to port" << PORT << ", occured in file: " << __FILE__ << ", line: " << __LINE__ << std::endl;
            return FAILED;
        }

        return SUCCESS;
    }

    /**
     * @brief Set the Address Configuration Structure
     * 
     * @param addressFamily Address family that should be set to the sockaddr structure
     * @param sAddr ip address
     */
    SocketStatus setAddressConfiguration(int addressFamily = AF_INET, uint32_t sAddr = INADDR_ANY)
    {
        address.sin_family = addressFamily;
        address.sin_addr.s_addr = sAddr;
        address.sin_port = htons(PORT);

        return SUCCESS;
    }

    /**
     * @brief Binds socket to the port specified in the constructor
     */
    SocketStatus bindSocket()
    {
        if ((bind(server_fd, (struct sockaddr *)&address, sizeof(address))) < 0)
        {
            printf("Failed to bind socket on port: %d, occured in file: %s, line: %d\n", PORT, __FILE__, __LINE__);
            return FAILED;
        }

        return SUCCESS;
    }

    /**
     * @brief Makes the socket alive on the port specified
     */
    SocketStatus listenSocket()
    {
        if (listen(server_fd, 3) < 0)
        {
            std::cout << "Failed to listen socket to port" << PORT << ", occured in file: " << __FILE__ << ", line: " << __LINE__ << std::endl;
            return FAILED;
        }

        return SUCCESS;
    }

    /**
     * @brief Accept new connections for this socket on the port specified
     * @returns {std::string} Returns the message from the client
     */
    std::string acceptNewSocket()
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            std::cout << "Failed to accept new socket to port" << PORT << ", occured in file: " << __FILE__ << ", line: " << __LINE__ << std::endl;
            exit(EXIT_FAILURE);
        }

        // set socket status
        state = ALIVE;

        valread = read(new_socket, (void *)buffer.c_str(), 1024);

        this->sendMessage();

        return buffer.c_str();
    }

    /**
     * @brief Sends a message to the client
     * The message will be the one used in the constructor parameters
     * @return SocketStatus {FAILED, SUCCESS}
     */
    SocketStatus sendMessage()
    {
        send(new_socket, message.c_str(), message.length(), 0);

        return SUCCESS;
    }

    /**
     * @brief Starts up the server and stays alive forever until the program is then finally terminated
     */
    void stayAlive()
    {
        while (true)
        {
            this->acceptNewSocket();
        }

        // set socket status
        state = DEAD; // socket is always dead after the termination of the forever loop
    }
};

/**
     * @brief Construct a new Client Socket object
     * Warning ⚠️: This does not initialize a socket, you need to do it manually by calling .initSocket() on your Socket object.
     * @param _PORT port to host the client-side connection to the server, this port should be the one used in the server-side socket to make sure you are connecting to the right one.
     * @param _message Message the server will recieve
     */
class SocketClient
{
private:
    int PORT;
    int sock, valread;
    struct sockaddr_in serv_addr;
    std::string buffer;
    std::string message;

public:
    SocketState state;

    /**
     * @brief Construct a new Client Socket object
     * Warning ⚠️: This does not initialize a socket, you need to do it manually by calling .initSocket() on your Socket object.
     * @param _PORT port to host the client-side connection to the server, this port should be the one used in the server-side socket to make sure you are connecting to the right one.
     * @param _message Message the server will recieve
     */
    SocketClient(int _PORT, std::string _message)
    {
        PORT = _PORT;
        message = _message;
        state = UNINITIALIZED;

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Client Side Socket creation failed. \n");
            exit(EXIT_FAILURE);
        }

        state = INITIALISED;
    }

    /**
     * @brief Set the Address Configuration object
     */
    SocketStatus setAddressConfiguration()
    {
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
        {
            printf("\nInvalid address || Address not supported \n");

            state = DEAD;

            return FAILED;
        }

        state = INITIALISED;

        return SUCCESS;
    }
    /**
     * @brief Connects the socket to the port
     */
    SocketStatus connectSocket()
    {
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)))
        {
            printf("\n Connection Failed \n");
            
            state = DEAD;

            return FAILED;
        }

        send(sock, message.c_str(), message.length(), 0);

        state = ALIVE;

        printf("Message sent\n");
        valread = read(sock, (void *)buffer.c_str(), 1024);
        printf("%s\n", buffer.c_str());

        return SUCCESS;
    }
};

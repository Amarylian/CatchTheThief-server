#ifndef SERVER_H
#define SERVER_H

#include "includes.h"

class Controller;

class Server
{
    public:
        Server();
        void start();
        virtual ~Server();
    protected:

    private:
        struct sockaddr_in server_address;
        int server_socket_descriptor;
        Controller* controller;

        void prepareSocket();
};

#endif // SERVER_H

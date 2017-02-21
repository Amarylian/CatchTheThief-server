#include "Server.h"

Server::Server()
{
    prepareSocket();
    controller = new Controller();

}

void Server::prepareSocket()
{
       server_address.sin_family = AF_INET;
       server_address.sin_addr.s_addr = htonl(INADDR_ANY);
       server_address.sin_port = htons(PORT_NUMBER);

       server_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
       if (server_socket_descriptor < 0)
       {
           cout << "Błąd przy próbie utworzenia gniazda..\n";
           exit(1);
       }
       cout << "Utworzono gniazdo.\n";

       char reuse_addr_val = 1;
       setsockopt(server_socket_descriptor, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse_addr_val, sizeof(reuse_addr_val));

       bool bind_result = bind(server_socket_descriptor, (struct sockaddr*)&server_address, sizeof(struct sockaddr));
       if (bind_result < 0)
       {
           cout<<"Błąd przy próbie dowiązania adresu IP i numeru portu do gniazda.\n";
           exit(1);
       }
       cout << "Dowiązano adres IP i numer portu do gniazda.\n";

       bool listen_result = listen(server_socket_descriptor, QUEUE_SIZE);
       if (listen_result < 0) {
           cout << "Błąd przy próbie ustawienia wielkości kolejki.\n";
           exit(1);
       }
       cout << "Ustawiono wielkość kolejki na " << QUEUE_SIZE<<"\n";

       cout << "Numer portu: "<<PORT_NUMBER<<"\n\n";
}

void Server::start()
{
    while(true)
    {
        int connection_socket_descriptor = accept(server_socket_descriptor, NULL, NULL);
        if (connection_socket_descriptor < 0)
        {
            cout<<"Błąd przy próbie utworzenia gniazda dla połączenia.\n";
            exit(1);
        }
        controller->newConection(connection_socket_descriptor);
        cout<<"Utworzono wątek dla połączenia\n";
    }
}

Server::~Server()
{
    close(server_socket_descriptor);
    cout<<"\nPoprawnie zamknięto socket\n";
    delete controller;
    cout<<"Poprwnie usunięto controller\n";
}

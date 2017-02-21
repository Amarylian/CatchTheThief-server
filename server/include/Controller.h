#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "includes.h"

class Player;
class Table;
class Message;

class Controller
{
    public:
        Controller();
        virtual ~Controller();

        void proceedMessage(Message* msg, Player* player);
        void newConection(int descriptor);

        //obsługa listy graczy
        void deletePlayer(Player* player);
        void deletePlayer(int i);
        Player* removePlayer(Player* player);
        Player* removePlayer(unsigned i);

    protected:
    private:
        std::vector<Player*> players;
        std::vector<Table*> tables;

        //obsługa listy stołów
        pthread_mutex_t tablesMutex;
        void lockTablesMutex(){pthread_mutex_lock(&tablesMutex);}
        void unlockTablesMutex(){pthread_mutex_unlock(&tablesMutex);}

        //obsługa list graczy
        pthread_mutex_t playersMutex;
        void lockPlayersMutex(){pthread_mutex_lock(&playersMutex);}
        void unlockPlayersMutex(){pthread_mutex_unlock(&playersMutex);}

        //obsługa wiadomości przychodzących
        int addTable(std::string name);
        int joinToTable(std::string name, Player* player);
        int listOfTables(std::vector<std::string>* tableList);

        void addPlayer(Player* player);
        bool tableExists(std::string name);
};

#endif // CONTROLLER_H

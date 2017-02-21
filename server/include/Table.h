#ifndef TABLE_H
#define TABLE_H

#include "includes.h"

class Table
{
    public:
        Table(std::string name);
        virtual ~Table();
        int joinTable(Player* p);
        void exitTable(Player* p);

        //gettery i settery
        std::string getName(){return name;}
    protected:
    private:
        std::string name;
        std::vector<Player*> players;

        pthread_mutex_t tableMutex;
        void lockMutex(){pthread_mutex_lock(&tableMutex);}
        void unlockMutex(){pthread_mutex_unlock(&tableMutex);}

};

#endif // TABLE_H

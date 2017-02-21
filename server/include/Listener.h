#ifndef LISTENER_H
#define LISTENER_H

#include "includes.h"

class Player;

class Listener
{
    public:
        Listener();
        Listener(int descriptor, Player* p);
        virtual ~Listener();
        static void* startThread(void* listener);
        void stopThread();
        bool sendMessage(Message* msg);

        //settery i gettery
        void setThread(pthread_t th);
        Player* getPlayer();
        int getSocketDescriptor();
        pthread_t getThread();

    protected:
    private:
        int socketDescriptor;
        Player* player;
        pthread_t thread;
        pthread_mutex_t criticalSection;

        void listen();
};

#endif // LISTENER_H

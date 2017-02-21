#ifndef PLAYER_H
#define PLAYER_H

#include "includes.h"

class Controller;
class Table;
class Listener;
class Message;

class Player
{
    public:
        Player();
        Player(int descriptor, Controller* c);
        virtual ~Player();

        void startPlayerThread();
        void stopPlayerThread();

        void proceedMessage(Message* msg);
        bool sendMessage(Message* msg);
        void prepareToDelete();

        //gettery i settery
        void setController(Controller* c);
        void setTable(Table* t);
        Table* getTable(){return table;}

    protected:
    private:
        Controller* controller;
        Table* table;
        Listener* listener;
};

#endif // PLAYER_H

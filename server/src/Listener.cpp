#include "Listener.h"

Listener::Listener(){
    socketDescriptor = -1;
    player = NULL;
    criticalSection=PTHREAD_MUTEX_INITIALIZER;
}

Listener::Listener(int descriptor, Player* p){
    this->socketDescriptor = descriptor;
    this->player = p;
    this->criticalSection=PTHREAD_MUTEX_INITIALIZER;
}

void* Listener::startThread(void* listener){
    Listener* l = (Listener*) listener;
    l->listen();

    cout<<"Zakończono nasłuchiwanie na "<<(l->getSocketDescriptor())<<"\n";

    l->getPlayer()->prepareToDelete();
    delete l->getPlayer();
    pthread_exit(NULL);
}

void Listener::stopThread(){
    pthread_mutex_lock(&criticalSection);
    pthread_cancel(this->thread);
    pthread_mutex_unlock(&criticalSection);
}

Player* Listener::getPlayer(){
    return this->player;
}

void Listener::listen()
{
    cout<<"Rozpoczęto nasuchiwanie od "<<this->socketDescriptor<<"\n";
    char c;
    string sMessage = "";
    while(read(this->socketDescriptor,&c,1)>0)
    {
        if(c==';')
        {
            cout<<"Odebrano: "<<sMessage<<"\n";
            Message* msg = new Message(sMessage);
            cout<<"RCV "<<this->socketDescriptor<<": "<<msg->toString()<<"\n";

            pthread_mutex_lock(&criticalSection);

            player->proceedMessage(msg);

            pthread_mutex_unlock(&criticalSection);

            delete msg;
            sMessage = "";
        }
        else sMessage = sMessage + c;
    }
}

bool Listener::sendMessage(Message* msg){
    string input = msg->toString();
    cout<<"SND "<<this->socketDescriptor<<": "<<msg->toString()<<"\n";
    if(0>send(socketDescriptor,input.data(),input.size(),0)){
        cout<<this->socketDescriptor<<": Nie udało się wysłać wiadomości\n";
        return false;
        }
    return true;
}

void Listener::setThread(pthread_t th)
{
    this->thread = th;
}

int Listener::getSocketDescriptor()
{
    return this->socketDescriptor;
}

Listener::~Listener(){ }

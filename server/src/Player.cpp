#include "Player.h"

Player::Player(int descriptor, Controller* c)
{
    this->controller = c;
    this->table = NULL;
    this->listener = new Listener(descriptor,this);
}

void Player::startPlayerThread()
{
    pthread_t thread;
    bool create_result = pthread_create(&thread, NULL, listener->startThread, (void *)listener);
    if (create_result){
       cout<<"Błąd przy próbie utworzenia wątku, kod błędu: "<<create_result<<"\n";
       exit(-1);
    }
    this->listener->setThread(thread);
}

void Player::stopPlayerThread()
{
    this->listener->stopThread();
}

void Player::setController(Controller* c)
{
    this->controller = c;
}

void Player::setTable(Table* t)
{
    this->table = t;
}

void Player::prepareToDelete()
{
    if(table!=NULL) table->exitTable(this);
    this->controller->removePlayer(this);
}

void Player::proceedMessage(Message* msg) {
    this->controller->proceedMessage(msg,this);
}

bool Player::sendMessage(Message* msg){
    return this->listener->sendMessage(msg);
}

Player::~Player()
{
    delete this->listener;
}

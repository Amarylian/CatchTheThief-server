#include "Controller.h"

Controller::Controller()
{
    playersMutex=PTHREAD_MUTEX_INITIALIZER;
    tablesMutex=PTHREAD_MUTEX_INITIALIZER;
    tables.reserve(TABLES_NUMBER);
    players.reserve(QUEUE_SIZE);
}

void Controller::proceedMessage(Message* msg, Player* player){
    Message* response = new Message();
    response->setCommand(msg->getCommand());
    int res;
    string command = msg->getCommand();

    //wykonanie akcji związanej z komendą
    if(command=="TABLE_CREATE"){
        res = addTable(msg->getArgument(0));
    }
    else if(command=="TABLE_JOIN"){
        res = joinToTable(msg->getArgument(0),player);
    }
    else if(command=="TABLE_LIST"){
        vector<string> tableList;
        res = listOfTables(&tableList);
        for(int i=0;i<res;i++) response->addArgument(tableList[i]);
    }
    else res=-1;

    //ustawienie treści błędu, jeśli akcja się nie powiodła
    if(res<0){
        response->setDecision("ERR");
        response->setErrorMessage(res);
    }
    else response->setDecision("ACK");

    //wysyłanie wiadomości
    int numberOfTry = 3;
    while(!player->sendMessage(response) && numberOfTry>0) numberOfTry--;
    if(numberOfTry==0) cout<<"Wysłanie odpowiedzi nie powiodło się\n";

    delete response;
}

int Controller::addTable(string name){
    //TODO: rozwiązać problem z wyrażeniem regularnym
    //if(!regex_match(name, regex("^[a-z]$"))) return -1;
    lockTablesMutex();
    if(tables.size()>=TABLES_NUMBER) {
        unlockTablesMutex();
        return -2;
        }
    if(tableExists(name)) {
        unlockTablesMutex();
        return -3;
        }
    Table* table = new Table(name);
    tables.push_back(table);
    unlockTablesMutex();
    return 0;
}

bool Controller::tableExists(string name){
    for(unsigned i=0;i<tables.size();i++)
        if(tables[i]->getName()==name)
            return true;
    return false;
}

int Controller::joinToTable(string name,Player* player){
    lockTablesMutex();
    int res = 0;
    if(player->getTable()!=NULL) res = -4;
    else if(!tableExists(name)) res = -3;
    else{
        unsigned i;
        for(i=0;i<tables.size();i++)
            if(tables[i]->getName()==name)
                break;
        res = tables[i]->joinTable(player);
    }

    unlockTablesMutex();
    return res;
}

int Controller::listOfTables(vector<string>* tableList){
    int res = -1;
    lockTablesMutex();
    for(unsigned i =0;i<tables.size();i++){
        tableList->push_back(tables[i]->getName());
        res = i+1;
    }
    unlockTablesMutex();
    return res;
}


void Controller::newConection(int descriptor){
    cout<<"Nowe połączenie\n";
    Player* p = new Player(descriptor, this);
    addPlayer(p);
    p->startPlayerThread();
}

void Controller::addPlayer(Player* player){
    lockPlayersMutex();
    players.push_back(player);
    unlockPlayersMutex();
}

void Controller::deletePlayer(Player* player){
    Player* p = removePlayer(player);
    delete p;
}

Player* Controller::removePlayer(Player* player){
    lockPlayersMutex();
    players.erase(remove(players.begin(), players.end(), player), players.end());
    unlockPlayersMutex();
    return player;
}

void Controller::deletePlayer(int i){
    Player* p = removePlayer(i);
    delete p;
}

Player* Controller::removePlayer(unsigned i){
    lockPlayersMutex();
    Player* p = NULL;
    if(i<players.size())
    {
        p = players[i];
        players.erase(players.begin()+i);
    }
    unlockPlayersMutex();
    return p;
}

Controller::~Controller(){
    while(players.size()!=0)
    {
        players[0]->stopPlayerThread();
        deletePlayer(0);
    }

    lockTablesMutex();
    while(tables.size()!=0)
    {
        delete tables[0];
        tables.erase(tables.begin());
    }
    unlockTablesMutex();
}

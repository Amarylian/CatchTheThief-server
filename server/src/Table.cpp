#include "Table.h"

Table::Table(std::string name){
    this->name = name;
}

int Table::joinTable(Player* p){
    lockMutex();
    int res=0;
    if(players.size()>=PLAYERS_NUMBER) res= -1;
    else if (std::find(players.begin(), players.end(), p) != players.end()) res=-2;
    else {
        players.push_back(p);
        p->setTable(this);
        }
    unlockMutex();
    return res;
}

void Table::exitTable(Player* p)
{
    lockMutex();
    players.erase(remove(players.begin(),players.end(),p),players.end());
    p->setTable(NULL);
    unlockMutex();
    cout<<"Opuszczono stół\n";
}

Table::~Table()
{
    //dtor
}

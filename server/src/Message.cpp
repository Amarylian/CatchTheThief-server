#include "Message.h"

Message::Message()
{
    command = "";
    decision = "";
}

Message::Message(string msg)
{
    vector<string> arg = split(msg);
    command = arg.front();
    decision = "";
    arg.erase(arg.begin());
    arguments = arg;
}

vector<string> Message::split(string msg)
{
    int i =0;
    int len = msg.length();
    vector<string> args;
    string s = "";
    while(i<len)
    {
        if(msg[i]!=' ') s=s+msg[i];
        else
        {
            args.push_back(s);
            s="";
        }
        i++;
    }
    args.push_back(s);
    return args;
}

string Message::argsToString()
{
    string res = "";
    int len = arguments.size();
    for(int i=0;i<len;i++)
    {
        if(i!=0) res = res + " ";
        res = res + arguments[i];
    }
    return res;
}

string Message::toString()
{
    string res = command;
    if(decision!="") res=res+" "+decision;
    if(arguments.size()>0) res = res+" "+argsToString();
    res = res +";";
    return res;
}


void Message::setErrorMessage(int errorCode)
{
    if(decision=="ERR"){
            if(command=="TABLE_CREATE"){
                switch(errorCode)
                {
                    case -1: addArgument("Nazwa stołu zawiera nieprawidłowe znaki.");break;
                    case -2: addArgument("Osiągnięto maksymalną liczbę stołów.");break;
                    case -3: addArgument("Stół o podanej nazwie już istnieje.");break;
                    default: addArgument("Nierozpoznany kod błędu.");break;
                }
            }
            else if(command=="TABLE_JOIN"){
                switch(errorCode)
                {
                    case -1: addArgument("Stół jest już w całości zajęty.");break;
                    case -2: addArgument("Należysz już do wybranej rozgrywki.");break;
                    case -3: addArgument("Stół o podanej nazwie nie istnieje.");break;
                    case -4: addArgument("Jesteś już przypisany do rozgrywki.");break;
                    default: addArgument("Nierozpoznany kod błędu.");break;
                }
            }
            else if(command=="TABLE_LIST"){
                switch(errorCode)
                {
                    case -1: addArgument("Nie utworzono jeszcze żadnego stołu do rozgrywki.");break;
                    default: addArgument("Nierozpoznany kod błędu.");break;
                }
            }
            else addArgument("Nie rozpoznano polecenia.");


    }

}

Message::~Message()
{
    //dtor
}

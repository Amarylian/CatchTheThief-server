#ifndef MESSAGE_H
#define MESSAGE_H

#include "includes.h"

class Message
{
    public:
        Message();
        Message(std::string msg);
        static std::vector<std::string> split(std::string msg);
        std::string argsToString();
        std::string toString();
        void addArgument(std::string arg){arguments.push_back(arg);}
        void setErrorMessage(int errorCode);
        virtual ~Message();

        //gettery i settery
        std::string getCommand(){return this->command;}
        std::string getDecision(){return this->decision;}
        std::vector<std::string> getArguments(){return this->arguments;}
        std::string getArgument(int i){return arguments[i];}
        int getNumberOfArguments(){return arguments.size();}
        void setCommand(std::string c){command=c;}
        void setDecision(std::string d){decision=d;}
        void setArguments(std::vector<std::string> args){arguments=args;}

    protected:
        std::string command;
        std::string decision;
        std::vector<std::string> arguments;
    private:
};

#endif // MESSAGE_H

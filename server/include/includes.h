#ifndef INCLUDES_H_INCLUDED
#define INCLUDES_H_INCLUDED

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <regex>


#include "Server.h"
#include "Player.h"
#include "Controller.h"
#include "Table.h"
#include "Listener.h"
#include "Message.h"

#define PORT_NUMBER 1235
#define QUEUE_SIZE 10
#define PLAYERS_NUMBER 4
#define TABLES_NUMBER 5

using namespace std;


#endif // INCLUDES_H_INCLUDED

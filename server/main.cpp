#include <includes.h>

Server* s;

void close_server(int signum)
{
    delete s;
    exit(0);
}

int main()
{
    signal(SIGINT, close_server);

    s = new Server();
    s->start();
    return 0;
}

#include "network.h"

int server(void){
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in server, cliaddr;
}
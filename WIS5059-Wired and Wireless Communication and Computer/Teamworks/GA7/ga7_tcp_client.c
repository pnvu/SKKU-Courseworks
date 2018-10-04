/*
Name: ga7_tcp_client.c
Description: Socket programming for client
Author: Phan Nguyen Vu
Date: 11th May 2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444

// function that receives and prints out message for thread
void* receive_msg(void *clientSocket){
    char buffer[1024];

    while(1){
        bzero(buffer, sizeof(buffer));
        if (recv(clientSocket, buffer, 1024, 0) < 0){
            perror("[-]Error in receiving data.\n\n");
        } else {
            printf("Other client: \t%s", buffer);
        }
    }
}

void* send_msg(char *buffer, int clientSocket){
    
}

int main() {

    int clientSocket, ret;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("[-]Error in connection.\n\n");
        exit(1);
    }
    puts("[+]Client Socket is created.\n\n");

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // connect
    ret = connect(clientSocket, (struct sockaddr*) &server_addr, sizeof(server_addr));
    if (ret < 0) {
        perror("[-]Error in connection.\n\n");
        exit(1);
    }
    puts("[+]Connected to Server.\n");

    // create thread to read and write message at the same time
    pthread_t t1;
    pthread_create(&t1,NULL,receve_msg,(void*)(intptr_t) clientSocket);

    while(1){
        fgets(buffer, 1024, stdin); //gets(message);
        send(clientSocket, buffer, strlen(buffer), 0);

        if (strcmp(buffer, "/quit") == 10) {
            close(clientSocket);
            perror("[-]Disconnected from server.\n\n");
            exit(1);
        }
    }
    pthread_join(t1, NULL);
    close(clientSocket);

    return 0;
}

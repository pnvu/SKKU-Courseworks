/*
Name: ga7_tcp_server.c
Description: Socket programming for server
Author: Phan Nguyen Vu
Date: 11th May 2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 4444   // port we're listening on

int main(void)
{
    fd_set master;    //master file descriptor list
    fd_set read_fds;  //temp file descriptor list for select()
    int fdmax;        //max. amount of file descriptors

    int listener;     //listening socket descriptor
    int newfd;        //newly accept()ed socket descriptor
    struct sockaddr_in client_addr; //client address
    socklen_t addrlen;

    char buffer[1024];    //bufferfer for client data
    int nbytes;

    int yes=1;        //for setsockopt() SO_REUSEADDR, below
    int i, j, rv;

    //struct addrinfo hints, *ai, *p;
    struct sockaddr_in server_addr;

    FD_ZERO(&master);    //FD_ZERO works like memset 0;
    FD_ZERO(&read_fds);  //clear the master and temp sets

    // fetch a socket, bind it
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0){
        printf("[+]Error in connection.");
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // lose the pesky "address already in use" error message
    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    // binding
    if (bind(listener, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("[-]Error in binding.\n");
        close(listener);
    }
    puts("[+]Binding successful!");

    // listen
    if (listen(listener, 10) == -1)
    {
        perror("[-]Error in listen.");
        exit(3);
    }
    puts("[+]Server is listening...");
    
    // add the listener to the master set
    FD_SET(listener, &master);

    // keep track of the biggest file descriptor
    fdmax = listener; //(it's this one so far)

    // main loop
    for(;;)
    {
        read_fds = master; // copy it
        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1)
        {
            perror("[-]Error in selecting.");
            exit(4);
        }

        //run through the existing connections looking for data to read
        for(i = 0; i <= fdmax; i++) //EDIT HERE
        {
            if (FD_ISSET(i, &read_fds))
            {   // we got one
                if (i == listener)
                {
                    // handle new connections
                    addrlen = sizeof client_addr;
                    newfd = accept(listener, (struct sockaddr *)&client_addr, &addrlen);

                    if (newfd == -1)
                    {
                        perror("[-]Error in accepting.");
                    }
                    else
                    {
                        FD_SET(newfd, &master); // pass to master set
                        if (newfd > fdmax)
                        {   // keep track of the max
                            fdmax = newfd;
                        }
                        printf("[+]New connection from %s on socket %d\n", inet_ntoa(client_addr.sin_addr), newfd);
                    }
                } 
                else
                {
                    // handle data from a client
                    if ((nbytes = recv(i, buffer, sizeof buffer, 0)) <= 0)
                    {   // got error or connection closed by client
                        if (nbytes == 0)
                        {   // connection closed
                            printf("[-]Socket %d disconnected.\n", i);
                        }
                        else
                        {
                            perror("[-]Error in receiving.");
                        }
                        close(i); // bye!
                        FD_CLR(i, &master); // remove from master set
                    }
                    else
                    {
                        // print data we get from a client
                        printf("Client %d: %s", i - 3, buffer);
                        for(j = 0; j <= fdmax; j++)
                        {
                            // broadcast to everyone
                            if (FD_ISSET(j, &master)) 
                            {
                                // except the listener and ourselves
                                if (j != listener && j != i)
                                {
                                    if (send(j, buffer, nbytes, 0) == -1)
                                    {
                                        perror("[-]Error in sending.");
                                    }
                                }
                            }
                        }
                        bzero(buffer, sizeof(buffer));
                    }
                }//handle data from client
            } //new incoming connection
        } //looping through file descriptors
    } //for(;;)
    
    return 0;
}
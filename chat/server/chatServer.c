#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMSZ 9

void broadcast(char* msg, int* clients, int numClients);

int main(int argc, char** argv)
{
    uint16_t port = 3000;
    struct sockaddr_in* server = malloc(sizeof(struct sockaddr_in));
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        puts("Bad Socket!!!!");
    }
    
    server->sin_family = AF_INET;
    server->sin_addr.s_addr = inet_addr("127.0.0.1");
    server->sin_port = htons( port );
    memset(server->sin_zero, '\0', sizeof server->sin_zero);

    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		perror("setsockopt");
		exit(1);
	}
    socklen_t serverSize = sizeof(server);
    
    int bindfd = bind(sockfd, (struct sockaddr *)server, sizeof(struct sockaddr));
    if(bindfd < 0)
    {
        puts("Problem with binding...\n");
    }
    int listenfd;
    int clientfd;
    int MAX_CLIENTS = 1000;
    int* clients = malloc(MAX_CLIENTS * sizeof(int));
    int numberOfConnectedClients = 0;
    
    
    //---------------------------------------------------
    int shmid;
    key_t key;
    //int *shm;

    /* We'll name our shared memory segment "5678".    */
    key = 5678;
    
    //Create the segment.
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        return -1;
    }
    //  Now we attach the segment to our data space. 
    if ((clients = shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        return -1;
    }
    /*/settting the scene
    int i = 1;
    for(; i < 10; i++)
    {
        shm[i] = '?';
    } */
    //----------------------------------------------------
    
    
    char* message = "Server says hello";
    
    while(1)
    {
        listenfd = listen(sockfd, 100);
    
        printf("Listening....\n");
        clientfd = accept(sockfd ,  (struct sockaddr *)server , &serverSize);
        
        printf("Client Connected.... %d\n", clientfd);
        int pid = fork(); 
        char* theReply = malloc(2000*sizeof(char));
        int error = recv(clientfd, theReply, sizeof(theReply), 0);
        if(error<0)
        {
            puts("recv failed");
        }
        else
        {
            puts("Some from client\n");
            message = theReply;
        }
        //add this client to our array of clients
        clients[numberOfConnectedClients++] = clientfd;
        
        //send(clientfd, message , strlen(message) , 0);
        broadcast(message, clients, numberOfConnectedClients);
    }
    //write(clientfd, buffer, sizeof(buffer));
}

void broadcast(char* msg, int* clients, int numClients)
{
    int i;
    for(i = 0; i < numClients; i++)
    {
        printf("Trying to send to client with FD: %d\n", clients[i]);
        //printf("Trying to send to client with FD: %d\n", *(clients + (i * sizeof(int))));
        
        send(clients[i] , msg , strlen(msg) , 0);
        puts("sent to client");
    }
}
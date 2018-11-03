//
//  main.c
//  Networks_lab1_server
//
//  Created by Gabriel Goteciuc on 13/10/2018.
//  Copyright © 2018 Gabriel Goteciuc. All rights reserved.
//

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void serveClient(int socket) {
    uint32_t sizeOfArray;
    uint32_t sum = 0;
    uint32_t sumNetwork;
    uint32_t networkElement;
    uint32_t sizeOfArrayNetwork;
    
    if (recv(socket, &sizeOfArrayNetwork, sizeof(sizeOfArrayNetwork), 0) < 0){
        printf("Receiving size failed\n");
        return;
    }
    sizeOfArray = ntohl(sizeOfArrayNetwork);
    for (int i = 0; i < sizeOfArray; ++i) {
        if (recv(socket, &networkElement, sizeof(networkElement), 0) < 0){
            printf("Receiving element failed\n");
            return;
        }
        sum += ntohl(networkElement);
    }
    
    sumNetwork = htonl(sum);
    
    if (send(socket, &sumNetwork, sizeof(sumNetwork), 0) < 0) {
        printf("Sending result failed\n");
        return;
    }
}

int main(int argc, const char * argv[]) {
    int listeningSocket;
    struct sockaddr_in server, client;
    int clientSocket;
    int sizeOfClient;
    
    listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(listeningSocket, (struct sockaddr *) &server, sizeof(server)) < 0){
        printf("Bind failed\n");
        exit(1);
    }
    
    if (listen(listeningSocket, 5) < 0){
        printf("Listen failed\n");
        exit(1);
    }
    
    sizeOfClient = sizeof(client);
    memset(&client, 0, sizeOfClient);
    
    while (1) {
        clientSocket = accept(listeningSocket, (struct sockaddr*)&client, (socklen_t*)&sizeOfClient);
        printf("%d connected\n", clientSocket);
        serveClient(clientSocket);
        close(clientSocket);
    }
    
    return 0;
}

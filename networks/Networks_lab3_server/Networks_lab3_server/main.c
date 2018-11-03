//
//  main.c
//  Networks_lab3_server
//
//  Created by Gabriel Goteciuc on 18/10/2018.
//  Copyright © 2018 Gabriel Goteciuc. All rights reserved.
//

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void serveClient(int socket) {
    char a[1024];
    
    if (recv(socket, a, sizeof(a), 0) < 0){
        printf("Receiving size failed\n");
        return;
    }
    printf("%s", a);
    for (int i = 0; i < 1024; ++i) {
        if (a[i] >= 'a' && a[i] <= 'z') {
            a[i] -= ' ';
        }
    }
    
    if (send(socket, a, strlen(a) + 1, 0) < 0) {
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
    
    if (listen(listeningSocket, 10) < 0){
        printf("Listen failed\n");
        exit(1);
    }
    
    sizeOfClient = sizeof(client);
    memset(&client, 0, sizeOfClient);
    
    while (1) {
        clientSocket = accept(listeningSocket, (struct sockaddr*)&client, (socklen_t*)&sizeOfClient);
        printf("%d connected\n", clientSocket);
        int c = fork();
        
        if (c < 0) {
            printf("Serving the client failed\n");
            continue;
        }
        
        if (c == 0) {
            serveClient(clientSocket);
            close(clientSocket);
            exit(1);
        }
    }
    
    return 0;
}

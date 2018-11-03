//
//  main.c
//  Networks_lab3_client_for_common_server
//
//  Created by Gabriel Goteciuc on 18/10/2018.
//  Copyright © 2018 Gabriel Goteciuc. All rights reserved.
//

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {
    
    int clientSocket;
    struct sockaddr_in server;
    char* a = "memed\0";
    char* b = malloc(sizeof(char) * (strlen(a) + 1));
    memset(b, 0, sizeof(char) * (strlen(a) + 1));
    
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0){
        printf("Socket failed\n");
        exit(1);
    }
    
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1235);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if(connect(clientSocket, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Connect failed\n");
        free(b);
        exit(1);
    }
    
    if (send(clientSocket, a, sizeof(char) * (strlen(a) + 1), 0) < 0) {
        printf("Sending size of array failed\n");
        free(b);
        exit(1);
    }
    
    if (recv(clientSocket, b, sizeof(char) * (strlen(a) + 1), 0) < 0) {
        printf("Receiving error\n");
        free(b);
        exit(1);
    }
    
    printf("%s\n", b);
    
    close(clientSocket);
    free(b);
    return 0;
}

//
//  main.c
//  Networks_lab1_client
//
//  Created by Gabriel Goteciuc on 13/10/2018.
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
    uint32_t sizeOfArray = 5;
    uint32_t a[] = {1, 2, 3, 4, 6};
    uint32_t sendValue = htonl(sizeOfArray);
    uint32_t sum;
    
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0){
        printf("Socket failed\n");
        exit(1);
    }
    
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if(connect(clientSocket, (struct sockaddr*)&server, sizeof(server)) < 0){
        printf("Connect failed\n");
        exit(1);
    }
    
    
    if (send(clientSocket, &sendValue, sizeof(sendValue), 0) < 0){
        printf("Sending size of array failed\n");
        exit(1);
    }
    
    for (int i = 0; i < sizeOfArray; ++i){
        sendValue = htonl(a[i]);
        if (send(clientSocket, &sendValue, sizeof(sendValue), 0) < 0) {
            printf("Sending array element failed\n");
            exit(1);
        }
    }
    
    if (recv(clientSocket, &sum, sizeof(sum), 0) < 0) {
        printf("Receiving error\n");
        exit(1);
    }
    
    printf("Sum is %u\n", ntohl(sum));
    
    close(clientSocket);
    return 0;
}

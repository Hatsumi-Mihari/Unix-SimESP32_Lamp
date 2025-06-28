//
// Created by Mihari Hatsumi on 20/6/25.
//

#ifndef INET_H
#define INET_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#ifdef __APPLE__
#include <malloc/malloc.h>
#define get_alloc_size(ptr) malloc_size(ptr)
#else
#include <malloc.h>
#define get_alloc_size(ptr) malloc_usable_size(ptr)
#endif


typedef struct InetSock {
    int sock;
    int port;
    struct sockaddr_in addr;
    struct sockaddr_in addrSrc;
    struct pollfd pollEvent;
    uint8_t *bufferRX;
    int sizeBuffer;
    ssize_t sizeBytesGeted;
}InetSock;

void UDPServerMake(InetSock *sock);
void UDPServerListen(InetSock *sock);
void UDPServerListen_callback(void *arg);

uint8_t *UDPGetData(InetSock *sock);
void debugNetwork (InetSock *sock);

#endif //INET_H

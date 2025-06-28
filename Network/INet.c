//
// Created by Mihari Hatsumi on 20/6/25.
//

#include "INet.h"
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>


void UDPServerMake(InetSock *sock) {
    sock->sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock->sock < 0) { perror("socket"); exit(EXIT_FAILURE); }
    sock->bufferRX = malloc(sock->sizeBuffer * sizeof(char));
    sock->addr.sin_family = AF_INET;
    sock->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sock->addr.sin_port = htons(sock->port);

    sock->pollEvent.fd = sock->sock;
    sock->pollEvent.events = POLLIN;

    if (bind(sock->sock, (struct sockaddr *)&sock->addr, sizeof(sock->addr)) < 0) {
        perror("bind"); close(sock->sock); exit(EXIT_FAILURE);
    }

    fcntl(sock->sock, F_SETFL, fcntl(sock->sock, F_GETFL) | O_NONBLOCK);
}

void UDPServerListen(InetSock *sock) {
    socklen_t addrLen = sizeof(sock->addrSrc);
    memset(&sock->addrSrc, 0, sizeof sock->addrSrc);

    sock->sizeBytesGeted = recvfrom(sock->sock, sock->bufferRX, sock->sizeBuffer, 0, (struct sockaddr *)&sock->addrSrc, &addrLen);
    if (sock->sizeBytesGeted < 0) { return; }

    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &sock->addrSrc.sin_addr, ip, sizeof(ip));
}

void UDPServerListen_callback(void *arg) {
    InetSock *sock = (InetSock*)arg;
    if (poll(&sock->pollEvent, 1, 50) > 0) {
        if (sock->pollEvent.revents & POLLIN) {
            UDPServerListen(sock);
        }
    }
}

uint8_t *UDPGetData(InetSock *sock) {
    return sock->bufferRX;
}

void debugNetwork (InetSock *sock) {
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &sock->addrSrc.sin_addr, ip, sizeof(ip));
    printf("Received %zd bytes from %s:%d", sock->sizeBytesGeted, ip, ntohs(sock->addrSrc.sin_port));
    putchar('\n');
}
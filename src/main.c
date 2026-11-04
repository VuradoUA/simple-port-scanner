#include <stdio.h>       // fprintf, printf
#include <arpa/inet.h>   // inet_ntop
#include <stdlib.h>      // strtol
#include "net.h"         // resolve_host, struct sockaddr_in

#define DEFAULT_TIMEOUT 2000 // in ms -> 2s

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        return 1;
    }

    const char *host = argv[1];
    char *end;
    long port = strtol(argv[2], &end, 10);
    if (end == argv[2] || *end != '\0' || port < 1 || port > 65535) {
        fprintf(stderr, "Invalid port: %s\n", argv[2]);
        return 1;
    }

    struct sockaddr_in target;
    if(resolve_host(host, &target) != 0) {
        return 1;
    }

    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &target.sin_addr, ip, sizeof ip);
    printf("Scanning %s port %ld\n", ip, port);

    return 0;

}


#include "net.h"
#include <stdio.h>      // fprintf, stderr
#include <string.h>     // memset
#include <sys/socket.h> // AF_INET, SOCK_STREAM
#include <netdb.h>      // getaddrinfo, freeaddrinfo, gai_strerror, struct addrinfo

int resolve_host(const char *host, struct sockaddr_in *out) {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof hints);
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(host, NULL, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "resolve %s: %s\n", host, gai_strerror(status));
        return -1;
    }

    *out = *(struct sockaddr_in *)res->ai_addr;
    freeaddrinfo(res);

    return 0;
}

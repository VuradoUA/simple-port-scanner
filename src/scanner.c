#include "scanner.h"    // own header first
#include <stdio.h>      // perror
#include <errno.h>      // errno, ECONNREFUSED
#include <unistd.h>     // close
#include <sys/socket.h> // socket, connect, AF_INET, SOCK_STREAM
#include <arpa/inet.h>  // htons

const char *port_state_str(enum port_state state) {
    switch(state) {
        case PORT_OPEN:     return "OPEN";
        case PORT_CLOSED:   return "CLOSED";
        case PORT_ERROR:    return "ERROR";
        case PORT_FILTERED:  return "FILTERED";
    }
    return "UNKNOWN";
}

enum port_state scan_port(const struct sockaddr_in *target, uint16_t port) {

    struct sockaddr_in addr = *target;
    addr.sin_port = htons(port);

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0) {
        perror("socket");
        return PORT_ERROR;
    }

    enum port_state state;
    if (connect(fd, (struct sockaddr *)&addr, sizeof addr) == 0) {
        state = PORT_OPEN;
    } else if (errno == ECONNREFUSED) {
        state = PORT_CLOSED;
    } else if (errno == ETIMEDOUT) {
        state = PORT_FILTERED;
    } else {
        state = PORT_ERROR;
    }
    close(fd);
    return state;
}


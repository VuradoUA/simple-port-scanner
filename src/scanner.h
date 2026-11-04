#ifndef SCANNER_H
#define SCANNER_H

#include <stdint.h>       // uint16_t
#include <netinet/in.h>   // struct sockaddr_in

enum port_state {
    PORT_OPEN,
    PORT_CLOSED,
    PORT_FILTERED,
    PORT_ERROR
};

// Tries a TCP connect to target:port and returns the resulting state.
// Does not print anything; the caller decides how to show the result.
enum port_state scan_port(const struct sockaddr_in *target, uint16_t port);

// Returns a printable name for a state ("OPEN", "CLOSED", ...).
const char *port_state_str(enum port_state state);

#endif
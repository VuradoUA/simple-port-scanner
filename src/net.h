#ifndef NET_H
#define NET_H

#include <netinet/in.h>   // struct sockaddr_in

// Resolves host (IP or hostname) into *out.
// Returns 0 on success, -1 on failure (prints the error).
int resolve_host(const char *host, struct sockaddr_in *out);

#endif
#ifndef PORTS_H
#define PORTS_H

#include <stdint.h>   // uint16_t
#include <stddef.h>   // size_t

// Parses a port spec like "22,80,100-200" into an array of ports.
// On success returns a malloc'd array (caller must free) and sets *count.
// On invalid input returns NULL and prints the error.
uint16_t *parse_ports(const char *spec, size_t *count);

// Reads a port number at *p, advances *p past it.
// Returns 0 on success, -1 if there is no valid number at *p.
static int read_port(const char **p, long *out);

// Appends a port to the array, growing it if needed.
// Returns 0 on success, -1 on allocation failure.
static int push_port(uint16_t **ports, size_t *count, size_t *capacity, uint16_t port);

#endif
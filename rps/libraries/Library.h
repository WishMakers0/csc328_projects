#ifndef _NETWLIB_H_
#define _NETWLIB_H_

#include <stddef.h>

// Display user-friendly error message and OS-Specific error message 
// If  errType is 0, use perror, else use strerror 
extern void error(char *errMsg, int errType, int errNum);

// Receives a message, and checks if it received the delimiter.
// Function has 3 returns: 0 for all is good, -1 for bad recv values (no comma, number, or delimiter), and -2 for failed recv.
// Parameters are all the parameters for recv, sans the length. Length is statically set to 32.
extern int recvDelim(int socket, char *buffer, int flags);

// Sends a message with requisite additions:
// Beginning of message, message type, and delimiter value.
// ,1READY@ is a functional message
    // , is begin of message
    // 1 is message type 'ready'
    // READY is text sent
    // @ is delimiter
    // int socket, void *buffer, size_t length, int flags, int messageType
extern int sendDelim(int sockfd, char *buffer, size_t length, int flags, int messageType);

// recvFinal simply takes the return value of recvDelim and does certain things with it depending on what that value is.
extern void recvFinal(int socket, char *buffer, int flags);

#endif

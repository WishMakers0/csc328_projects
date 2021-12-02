#ifndef _NETWLIB_H_
#define _NETWLIB_H_

#include <stddef.h>

// Display user-friendly error message and OS-Specific error message 
// If  errType is 0, use perror, else use strerror 
extern void error(char *errMsg, int errType, int errNum);

// Receives a message, and checks if it received the delimiter.
// If not, it clears the buffer and tries again.
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

#endif

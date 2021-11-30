#ifndef _NETWLIB_H_
#define _NETWLIB_H_

#include <stddef.h>

// Display user-friendly error message and OS-Specific error message 
// If  errType is 0, use perror, else use strerror 
extern void error(char *errMsg, int errType, int errNum);

// Receives a message, and checks if it received the delimiter.
// If not, it clears the buffer and tries again.
extern int recvDelim(int socket, char *buffer, size_t length, int flags);

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

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "netwLib.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>



// Display user-friendly error message and OS-Specific error message 
// If  errType is 0, use perror, else use strerror 
/* Parameters:
*  errMsg:  The message to print
*  errType: Whether the error message is to use perror or strerror 
*  errNum:  What sterror prints with system error code errnum. This value is retrieved by system call returns.
*/
void error(char *errMsg, int errType, int errNum) { 
    if (errType == 0){ 
        perror(errMsg);
    }
    else { 
        printf("%s", errMsg); 
        strerror(errNum);
    }
return; 

}


int sendDelim(int sockfd, char *buffer, size_t length, int flags, int messageType){
    char truemessage[length + 3];
    int looper;
    int err;
    char errsend[19] = "Error: Send failed";
    
    truemessage[0] = ',';
    truemessage[1] = messageType + '0';
    for(looper = 0; looper < length; looper++){
        truemessage[looper+2] = buffer[looper];
    }
    truemessage[looper+1] = '@';
    err = send(sockfd, truemessage, looper, flags);
    if(err < 0){
        error(errsend, 0, errno);
        return -1;
    }
    printf("%s", truemessage);
    return 0;
}

int recvDelim(int socket, char *buffer, size_t length, int flags){
    int err;
    int attempts;
    char errRcv[22] = "Error: Receive failed";
    
    for(attempts = 0; attempts < 5; attempts++){
        err = recv(socket, buffer, length, flags);
        if(err < 0){
            error(errRcv, 0, errno);
        }
        if(buffer[0] == ',' && (buffer[1] > 47 && buffer[1] < 58) && buffer[length-1] == '@'){
            return 0;    
        }
    }
    
    return -1;
    
}
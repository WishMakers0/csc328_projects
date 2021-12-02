/*   Author:           Boyd Lenich                   */
/*   Major:            Computer Science              */
/*   Creation Date:    November 27 2021               */
/*   Due Date:         December 2 2021               */
/*   Course:           CSC 328                       */
/*   Professor:        Dr. Frye                      */
/*   Assignment:       RPS - Server                  */
/*   Filename:         Server.c                      */
/*	 Language:		   C                             */
/*	 Version:		   8.3.0                         */
/*   Command:                                        */
/*   Purpose:                                        */
			
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
//#include "lib.h"

int main(int argc, char *argv[]){
	int pfd1[2];
	int pfd2[2];
	pid_t pid; 
	pid_t ppid = getppid();
	int sockfd, connfd, conn2fd ,len, port, clilen;
	struct sockaddr_in servaddr, cliaddr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(argc == 2){
	printf("yes 1");
	
	}else if(argc == 3){
	printf("yes 2");
	port = atoi(argv[2]);
	printf("PORT %d", port);
	}else{  //checks for right number of input
		printf("\n Usage: %s <number of rounds> <port number>\n\n", argv[0]);
		exit(-1);
	}
	//assign port and ip address for socket
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);
	//binds the host socket
	bind(sockfd, (struct sockaddr *) $servaddr, sizeof(struct sockaddr));
	//starts listening for connections to the host socket
	listen(sockfd, 1024);
	
	while(1){
		//waiting for player 1
		if( (connfd = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen)) <0){
			if ((errno == EINTR) || (errno == ECONNABORTED))
				continue;         // back to while() 
			 else
              {
                perror("accept error");
                exit(-1);   // possibly change to continue, depends on functionality. 
              }   // end else
          }   // end if accept
	  //waits for second player
	  if( (conn2fd = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen)) <0){
			if ((errno == EINTR) || (errno == ECONNABORTED))
				continue;         // back to while() 
			 else
              {
                perror("accept error");
                exit(-1);   // possibly change to continue, depends on functionality. 
              }   // end else
          }   // end if accept
		if ( (childpid = fork()) == 0) {      // child process made. 
            close(sockfd);        //close listening socket; only with child 
            /*here is where an rps match function will go, in a loop equal to the number of matches,
			it will return the data needed for the clients,
			TO DO:Finish pipe functionality, Look for inevitable bugs, functions, cleaning, and testing.*/
            close(connfd);     
			close(conn2fd)
            exit(0);
          }  // end if: child process
		}
	}	
}

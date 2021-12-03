/*   Author:           Boyd Lenich                   */
/*   Major:            Computer Science              */
/*   Creation Date:    November 27 2021              */
/*   Due Date:         December 2 2021               */
/*   Course:           CSC 328                       */
/*   Professor:        Dr. Frye                      */
/*   Assignment:       RPS - Server                  */
/*   Filename:         Server.c                      */
/*	 Language:		   C                 */
/*	 Version:		   8.3.0             */
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

#define LISTENQ   1024
#define MAX   256
/*************************************************************************/
/* 									 */
/* Function name: connp                                                  */                                
/* Description: connects players                                         */
/* Parameters:   
    sockfd:Host socket
	connfd:Client socket
	cliaddr:Client address
	clilen:Length of client adress                                    */
/* Return Value: none                                                    */
/*                                                                       */
/*************************************************************************/
void connp(int sockfd, int connfd,  struct sockaddr cliaddr, int clilen){
	
	if( (connfd = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen)) <0){
			if ((errno == EINTR) || (errno == ECONNABORTED))
				continue;         // back to while() 
			 else
              {
                perror("accept error");
                exit(-1);   // possibly change to continue, depends on functionality. 
              }   // end else
          }   // end if accept
	
						
}

/*************************************************************************/
/* 																		 */
/* Function name: rpsRun                                                 */                                
/* Description: runs each match                                          */
/* Parameters:                                                           */
/* Return Value: none                                                    */
/*                                                                       */
/*************************************************************************/
void rpsRun(){
	
	
	
	
			
	
	
}

/*************************************************************************/
/* 																		 */
/* Function name: startCheck                                              */                                
/* Description: Checks nickname uniqueness                               */
/* Parameters:                                                           */
/* Return Value: none                                                    */
/*                                                                       */
/*************************************************************************/
void startCheck(ppid, connfd, conn2fd){
	pid_t pid;
	pid_t pid2;
	char buff1[MAX], buff2[MAX];
	char *b1 = buff1, *b2 = buff2;
	char tbuff1[MAX}, tbuff2[MAX]
	char *tb1 = tbuff1, *tb2 = tbuff2;
	
	
	if ( (pid = fork()) == 0) {      // child process made. 
		close(p1sen[1]);
		close(p1rec[1]);
		connp(sockfd, connfd, cliaddr, clilen); //waiting for player 1
		recvFinal(connfd, buff1, 0);
		b1 = b1+2;
		strncpy(tbuff1, buff1,5);
		if(strncmp(tbuff1, "READY", 5)){
			recvFinal(connfd, buff1, 0);
			b1 = b1+2;
			strncpy(tbuff1, buff1,30);
			if(strncmp(tbuff1, "NICK", 4)){
				tb1=tb1+4;
			}
		}
	}
	if (pid > 0){ //Parent
		if ( (pid2 = fork()) == 0) {      // child process 2 made. 
			close(p2sen[1]);
			close(p2rec[1]);
			connp(sockfd, conn2fd, cliaddr, clilen); //waits for player 2
			recvFinal(conn2fd, buff2, 0);
			b2 = b2+2;
			strncpy(tbuff2, buff2,5);
			if(strncmp(tbuff1, "READY", 5)){
				recvFinal(conn2fd, buff2, 0);
				b2 = b2+2;
				strncpy(tbuff2, buff2,30);
				if(strncmp(tbuff2, "NICK", 4)){
					tb2=tb2+4;
				}
			}
		}
	while(){

	}
	close(p1sen[0]);
	close(p2sen[0]);
	close(p1rec[0]);
	close(p2rec[0]);
	
	}
	
	
}
/*************************************************************************/
/* 																		 */
/* Function name: checkRec                                               */                                
/* Description: runs each match                                          */
/* Parameters:                                                           */
/* Return Value: none                                                    */
/*                                                                       */
/*************************************************************************/
checkRec(int check){
	if(check = -2)
		exit(-1);
	if(check = -1)
		
}

int main(int argc, char *argv[]){
	int p1sen[2];
	int p2sen[2];
	int p1rec[2];
	int p2rec[2];
	pipe(p1sen);
	pipe(p2sen);
	pipe(p1rec);
	pipe(p2rec);
	fcntl(p1sen[], F_SETFL, 0_NONBLOCK);
	fcntl(p2sen[], F_SETFL, 0_NONBLOCK);
	fcntl(p1rec[], F_SETFL, 0_NONBLOCK);
	fcntl(p2rec[], F_SETFL, 0_NONBLOCK);
	pid_t ppid = getppid();
	int sockfd, connfd, conn2fd ,len, port, clilen, numg;
	struct sockaddr_in servaddr, cliaddr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0;

	if(argc == 2){
		printf("yes 1");
		numg = atoi(argv[1]);
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
	
	bind(sockfd, (struct sockaddr *) $servaddr, sizeof(struct sockaddr)); //binds the host socket
	
	listen(sockfd, LISTENQ); //starts listening for connections to the host socket
	
	while(1){
		
	
		
		
	    

		close(sockfd);        //close listening socket; only with child 
		close(pfd1[1]);
		close(pfd2[1]);
		//setup match here.
		
		
		//NOTE: NEED WAY TO PROCESS THE BUFFER TO GET THE RAW MESSAGE
		nickCheck();
		
			rpsRun(connfd, conn2fd);
		}
		close(connfd);     
		close(conn2fd);
		exit(0);
	  }  // end if: child process
	
		}
	}
	
	
}

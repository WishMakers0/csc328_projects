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
#define NICKSIZE 24
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
/* 									 */
/* Function name: rpsRun                                                 */                                
/* Description: runs each match                                          */
/* Parameters:                                                           */
/* Return Value: none                                                    */
/*                                                                       */
/*************************************************************************/
void rpsRun(){
	
}

/*************************************************************************/
/* 									 */
/* Function name: isReady                                                */                                
/* Description: if ready, returns true                                   */
/* Parameters:                                                           */
/* Return Value: none                                                    */
/*                                                                       */
/*************************************************************************/
bool isReady(connfd){
	char buff[MAX];  //Buffer where the message is originally sent.
	char tbuff[MAX]; // The function that takes in the processed data.
	recvFinal(connfd, buff, 0);
}

/*************************************************************************/
/* 									 */
/* Function name: getName                                                */                                
/* Description: Grabs name and returns it                                */
/* Parameters:                                                           */
/* Return Value: name chosen                                             */
/*                                                                       */
/*************************************************************************/
char getName(int connfd, bool retry){
	char buff[MAX];
	char tbuff[MAX];
	if(retry == TRUE){
		sendDelim(connfd, "RETRY", sizeof("RETRY"), 0, 4);	
		
	}
	recvFinal(connfd, buff, 0);
	
	return tbuff[];
	
}

/*************************************************************************/
/* 									 */
/* Function name: pipeSet                                                */                                
/* Description: sets up pipe                                             */
/* Parameters:     pipe                                                  */
/* Return Value: none                                                    */
/*                                                                       */
/*************************************************************************/
void setpipe(int *pipe){
	pipe(pipe);
	fcntl(pipe[], F_SETFL, 0_NONBLOCK);
	
}
/*************************************************************************/
/* 									 */
/* Function name: startCheck                                             */                                
/* Description: Checks nickname uniqueness                               */
/* Parameters:                                                           */
/* Return Value: none                                                    */
/*                                                                       */
/*************************************************************************/
void startCheck(ppid, connfd, conn2fd){
	pid_t pid;
	pid_t pid2; //the 2 pids possibly not needed
	char buff1[MAX], buff2[MAX]; //buffs from clients
	int namesize = 0; //starting name size
	int block1= -1, block2 = -1; //needed for non blocking run of read. 
	int first; //will be set to either 1 or 2 depending on who typed name first.
	char name1[NICKSIZE];
	char name2[NICKSIZE];
	
	if ( (pid = fork()) == 0) {      // child process made. 
		close(p1rec[0]);
		connp(sockfd, connfd, cliaddr, clilen); //waiting for player 1
		
		b1 = b1+2;
		strncpy(tbuff1, buff1,5);
		if(strncmp(tbuff1, "READY", 5)){
			recvFinal(connfd, buff1, 0);
			b1 = b1+2;
			strncpy(tbuff1, buff1,30);
			if(strncmp(tbuff1, "NICK", 4)){
				tb1=tb1+4;
				write(p1sen[1], &tbuff1, sizeof(tbuff1));
			}
		}
	}
	if (pid > 0){ //Parent
		if ( (pid2 = fork()) == 0) {      // child process 2 made. 
			close(p2rec[0]);
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
					write(p2sen[1], &tbuff2, sizeof(tbuff2));
				}
			}
		}

		//parent
		close(p1sen[0]);
		close(p2sen[0])
		while(block1 == -1 || block2 ==-1){
			block1 = read(p1[sen], &tbuff1, sizeof(tbuff1));

			block2 = read(p2[sen], &tbuff2, sizeof(tbuff2));

		}
		if(block1 ==-1){
			for(i = 0; buffer2[i] != @; i++){
				name2[i] = buffer2[i];
				namesize++;
			}
		first = 2;
		}else{
			for(i = 0; buffer1[i] != @; i++){
				name1[i] = buffer1[i];
				namesize++;
			}
		first = 1;
		}
		while(strncmp(name1,name2, namesize)){
			if(block1 ==-1){
				while(block1 == -1){
					block1 = read(p1[sen], &tbuff1, sizeof(tbuff1));
				}
			
			}else{
				while(block2 == -1){
					block2 = read(p2[sen], &tbuff2, sizeof(tbuff2));	
				}
			}
			if(first = 1){
				if(strcmp(name1, name2, namesize)){
					
				}

			}else if(first = 2){

			}
		}
		
	}
	
	
}


int main(int argc, char *argv[]){
	int p1sen[2];
	int p2sen[2];
	int p1rec[2];
	int p2rec[2];
	setPipe(p1sen[2]);
	setPipe(p2sen[2]);
	setPipe(p1rec[2]);
	setPipe(p2rec[2]);
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

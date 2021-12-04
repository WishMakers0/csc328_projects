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
#include <fcntl.h>
#include "Library.h"

#define LISTENQ   1024
#define MAX   256
#define NICKSIZE 24


/*
Function name: strsub
Description: 
    Gets a substring from our packet format (ignores the comma, message type, and delimiter)

Parameters: char* buffer -  original string
            char* to - where to put the substring
Return value: int - size of the substring
*/
int strsub(char *buffer, char* to) {
    char* start = &buffer[2];
    int length = 0;
    char* i = start;
    while(!((*i == '@') || (length > 253))) { //pointer arithmetic, fun
        length++; i++;
    }
    if (length > 253) {
        //error: out of bounds write?  improperly formatted packet?  either way something's wrong
    }
    strncpy(to, start, length);
    return length;
}

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
void connp(int *sockfd, int *connfd,  struct sockaddr *cliaddr, int clilen){

	if( (*connfd = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen)) <0){
			if ((errno == EINTR) || (errno == ECONNABORTED))
				continue;         // back to while() 
			 else{
		perror("accept error");
		exit(-1);   // possibly change to continue, depends on functionality. 
	      }   // end else
	  }   // end if accept	
	return;
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
/* Function name: nameFirst                                              */                           
/* Description: recieves names form child based on which one is first    */
/* Parameters:                                                           */
/* Return Value: none                                                    */
/*                                                                       */
/*************************************************************************/
int nameFirst(int *pipe1, int *pipe2, char  *name1, char  *name2, char  *name1size, char  *name2size){
	int block1 = -1, block2 = -1;
	while(block1 == -1 || block2 ==-1){
			block1 = read(*pipe1[0], *name1, sizeof(name1));

			block2 = read(*pipe2[0], *name2, sizeof(name2));

		}
	if(block1 = -1){
		name2size = read(*pipe2[0], *name2, sizeof(name2));
		return(2);
	}
	if(block2 = -1){
		name1size = read(*pipe1[0], *name1, sizeof(name1));
		return(1);
	}
	
}

/*************************************************************************/
/* 									 */
/* Function name: nameSecond                                            */                           
/* Description: takes in the second name for comparison                 */
/* Parameters:                                                           */
/* Return Value: none                                                    */
/*                                                                       */
/*************************************************************************/
void nameSecond(int *pipe, char  *name, char  *namesize){
	while(block == -1){
			block = read(pipe[0], &name, sizeof(tbuff));
		}
	read(pipe[0], &namesize, sizeof(namesize));
}


/*************************************************************************/
/* 									 */
/* Function name: isReady                                                */                                
/* Description: if ready, returns true                                   */
/* Parameters:                                                           */
/* Return Value: none                                                    */
/*                                                                       */
/*************************************************************************/
int isReady(int *connfd){
	char buff[MAX];  //Buffer where the message is originally sent.
	char tbuff[MAX]; // The function that takes in the processed data.
	recvFinal(connfd, buff, 0);
	strsub(buff[], tbuff[]);
	return(strncmp(tbuff[], "READY", 5));
}

/*************************************************************************/
/* 									 */
/* Function name: getName                                                */                                
/* Description: Grabs name, ships it and size to pipe                    */
/* Parameters:                                                           */
/* Return Value: name chosen                                             */
/*                                                                       */
/*************************************************************************/
void getName(int *connfd, bool retry, int *pipe){
	char buff[MAX];
	char tbuff[MAX];
	char finbuff[MAX];
	int nsize; //size of the name
	if(retry == TRUE){
		sendDelim(connfd, "RETRY", sizeof("RETRY"), 0, 4);	
		
	}
	recvFinal(connfd, buff, 0);
	nsize = strsub(buff[], tbuff[]);
	if(strncmp(tbuff, "NICK", 4)){
		finbuff[] = *tbuff[4];
		write(pipe[1], &finbuff, sizeof(finbuff));
		write(pipe[1], size, sizeof(size));
	}
	return;
	
}

/*************************************************************************/
/* 									 */
/* Function name: pipeSet                                                */                                
/* Description: sets up pipe                                             */
/* Parameters:     pipe                                                  */
/* Return Value: none                                                    */
/*                                                                       */
/*************************************************************************/
void setpipe(int *pip){
	pipe(*pip);
	fcntl(pipe[], F_SETFL, 0_NONBLOCK);
	return;
}
/*************************************************************************/
/* 									 */
/* Function name: startCheck                                             */                                
/* Description: Checks nickname uniqueness                               */
/* Parameters:                                                           */
/* Return Value: none                                                    */
/*                                                                       */
/*************************************************************************/
/*
void startCheck(ppid, connfd, conn2fd){
	pid_t pid;
	pid_t pid2; //the 2 pids possibly not needed
	char buff1[MAX], buff2[MAX]; //buffs from clients
	int namesize = 0; //starting name size
	int block1= -1, block2 = -1; //needed for non blocking run of read. 
	int first; //will be set to either 1 or 2 depending on who typed name first.
	char name1[NICKSIZE];
	char name2[NICKSIZE];
	qsock = socket(AF_INET, SOCK_STREAM,0)
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
*/

int main(int argc, char *argv[]){
	struct sockaddr_in      cliaddr, servaddr;
	int sockfd;
	sockfd = socket(AF_INET, SOCK_STREAM,0)
	int p1sen[2];
	int p2sen[2];
	int p1rec[2];
	int p2rec[2];
	setPipe(p1sen[2]);
	setPipe(p2sen[2]);
	setPipe(p1rec[2]);
	setPipe(p2rec[2]);
	pid_t pid1;
	pid_t pid2; //the 2 pids possibly not needed
	char buff1[MAX], buff2[MAX]; //buffs from clients
	int nsize1, nsize2; //starting name size
	int block1= -1, block2 = -1; //needed for non blocking run of read. 
	int first; //will be set to either 1 or 2 depending on who typed name first.
	int numg; //number of games to be played
	char name1[NICKSIZE];
	char name2[NICKSIZE];
	
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
	memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family      = AF_INET;
        // accept incoming connections on any interface on the server
        servaddr.sin_addr.s_addr = INADDR_ANY;
        // accept incoming connections on specified port number, converted to network byte order
        servaddr.sin_port        = htons(port));
	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(struct sockaddr));
	while{
		if ( (pid1 = fork()) == 0) {      // child process made. 

			close(p1rec[0]);
			connp(sockfd, conn1fd, cliaddr, clilen); //waiting for player 1
			if(isReady(conn1fd) == 0){
				getName(conn1fd, FALSE, *p1sen[]);
			}else{
				printf("Error with isReady()");
			}

		}
		if (pid > 0){ //Parent

			if ( (pid2 = fork()) == 0) {      // child process 2 made. 
				close(p2rec[0]);
				connp(sockfd, conn2fd, cliaddr, clilen); //waits for player 2
				if(isReady(conn1fd) == 0){
					getName(conn2fd, FALSE, *p2sen[]);
				}else{
				printf("Error with isReady()");
				}
			}//START OF PARENT

			first = nameFirst(*p1sen[], *p2sen[], *name1, *name2, *nsize1, *nsize2);
			if(first==1){
				nameSecond(*p2sen[], *name2, *nsize2);
				if(nsize2 == nsize1){
					if(strncmp(name1, name2, nsize1)){
						write(p1rec[1], "RETRY", sizeof("RETRY")); 
					}
				}
			}else if(first==2){
				nameSecond(*p1sen[], *name1, *nsize1);
				if(nsize2 == nsize1){
					if(strncmp(name1, name2, nsize1)){
						write(p2rec[1], "RETRY", sizeof("RETRY")); 
					}
				}
			}else{
			printf("error with nameFirst");	
			}

			close(sockfd);        //close listening socket; 
			close(p1rec[1]);
			close(p2rec[1]);



			close(conn1fd);     
			close(conn2fd);
			exit(0);



		}
	}
	
}

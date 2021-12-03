/*
	Author: Daniel Oravetz
	Major: Computer Science
	Creation Date: November 30, 2021
	Due Date: December 3, 2021
	Course: CSC328-010
	Professor Name: Dr. Frye
	Assignment: RPS Project - Client Portion
	Filename: client.c
	Purpose: 

	Run command: ./client.out <ip_address> <port num>
	Compile command: 
		make build_client
        *OR*
        make build_all

	<end>
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>
#include "Library.h"

//preprocessor defines
#define MAXCHARS 256
#define NICKSIZE 24
#define NICKBUFFER 32

//enum for constants declared in place of a million preprocessor definitions
typedef enum MessageType { Ready=1, Go=2, Nick=3, Retry=4, RPS=5, Score=8, Stop=9 } MessageType;

//Note 1: spit out error message and prompt for another message?
//Classic Two Generals' Problem - https://www.youtube.com/watch?v=IP-rGJKSZ3s

/*
Function name: finalDisplay
Description: 

Parameters: 
Return value: 
*/
void finalDisplay(char* buffer) {
	//Process copy buffer from processed message to display final score results.
	//example packet: SCORE
	
	//wait until later
}

/*
Function name: getTrueMessageLength
Description: 

Parameters: char* buffer - the received full message

Return value: int length - the length of the "true" message within an encoded packet
*/

int getTrueMessageLength(char* buffer) {
	//first two characters are always , followed by a number for the type - start indexing at 2
	int length = 0;
	bool atFound = false;
	for(int i = 2; (i < MAXCHARS) || !atFound; i++) {
		if (buffer[i] == '@') {
			atFound = true;
		}
		else {
			length++;
		}
	}
	return length;
}

/*
Function name: parseMessage
Description: 

Parameters: char* buffer - the received message to translate
			MessageType type - the message type to check for

Return value: bool success - success/failure upon parsing message
*/

bool parseMessage(char* buffer, MessageType type) {
	bool result = true;
	char copyBuffer[MAXCHARS];

	//Sanity check to ensure encoded message's validity.
	if (buffer[0] != ',') {
		result = false;
		//error?
	}

	//Verifying if the type of the message is what we expect.
	int encodedType = buffer[1] - '0';
	if (encodedType != (int)type) {
		result = false;
		//error?
	}

	//Copy "true message" to copyBuffer to strcmp with the expected message.
	int messageLength = getTrueMessageLength(buffer);
	strncpy(copyBuffer, &buffer[2], messageLength);

	//Switch statement for different message types.
	switch(type) {
		case Ready:
			if (strncmp(copyBuffer,"READY",5)) {
				result = true;
			}
			break;
		case Go:
			if (strncmp(copyBuffer,"GO",2)) {
				result = true;
			}
			break;
		case Retry:
			if (strncmp(copyBuffer,"RETRY",5)) {
				result = true;
			}
			break;
		case RPS:
			if (strncmp(copyBuffer,"ROCK",4) || strncmp(copyBuffer,"PAPER",5) || strncmp(copyBuffer,"SCISSORS",8)) {
				//return result to a specific variable if applicable?
				result = true;
			}
			break;
		case Score:
			if (strncmp(copyBuffer,"SCORE",5)) {
				result = true;
				//process other parts of score in remaining segment of message?
				finalDisplay(copyBuffer);
			}
			break;
		case Stop:
			if (strncmp(copyBuffer,"STOP",4)) {
				result = true;
			}
			break;
		default:
			result = false;
			//error("Non-parsible message type?",,);
			break;
	}
	return result;
}

/*
Function name: recvWrap
Description: 

Parameters: int* sock - socket file descriptor //could be replaced with int?
			char* buffer - buffer to write to
			MessageType type - type of message to check for
			size_t length - length of message to check
Return value: 
*/
void recvWrap(int sock, char* buffer, MessageType type, size_t length) {
	recvDelim(sock, buffer, 0);
	if(!parseMessage(buffer, type)) {
		//see Note 1
	}
}

/*
Function name: establishConnection
Description: 

Parameters: char* ip - ip address specified
			int port - port number specified
			int* socket - pointer to socket int
Return value: 
*/
int establishConnections(char* ip, int port, int* sock, struct sockaddr_in* server_addr, char* buffer) {
	*sock = socket(AF_INET, SOCK_STREAM, 0); //establish socket file descriptor

	//create memory and initialize sockaddr
	memset(server_addr, 0, sizeof(struct sockaddr));
	server_addr->sin_family = AF_INET;
    server_addr->sin_addr.s_addr = inet_addr(ip);
    server_addr->sin_port = htons(port);

	//binds the host socket
	bind(*sock, (struct sockaddr*)server_addr, sizeof(struct sockaddr_in));
	
	//connects to server socket
	if (connect(*sock, (struct sockaddr*)server_addr, sizeof(struct sockaddr_in)) != 0) {
		//error!
		return -1;
	}

	sendDelim(*sock, "READY", 5, 0, Ready);
	printf("Connection with server successful.  Waiting for server response...");
	recvWrap(*sock, buffer, 8, Ready);
	return 0;
}

/*
Function name: nameEntry
Description: 

Parameters: 
Return value: 
*/

void nameEntry(char* nick, char* buffer, int sock) {
	//Obvious note to future self: when parsing nickname options PLEASE make sure there aren't any digits, commas, or at signs
	bool confirm = false;
	while (!confirm) {
		printf("Enter a display name (max 24 characters): ");
		fgets(nick, NICKSIZE, stdin);

		printf("Confirming...\n");
		confirm = true;
		for(int i = 0; i < NICKSIZE; i++) {
			if (nick[i] == ',' || nick[i] == '@' || nick[i] > 47 || nick[i] < 58) {
				confirm = false;
				printf("Display name can not contain digits, commas, or the at sign.  Try again.\n");
			}
		}

		//Sends nickname packet
		strncpy(buffer, "NICK", 4);
		strncat(buffer, nick, NICKSIZE);
		sendDelim(sock, buffer, NICKBUFFER, 0, Nick);

		//Waits for server response
		printf("Waiting for server...");
		recvDelim(sock, buffer, 0);
		if(parseMessage(buffer, Ready)) {
			confirm = true;
			printf("Nickname approved.  Waiting for opponent...\n");
		}
		else if(parseMessage(buffer, Retry)) {
			confirm = false;
			printf("Nickname denied - same as opponent.  Try again.\n");
		}
		else {
			//See Note 1.
		}
	}
}

/*
Function name: awaitGo
Description: 

Parameters: 
Return value: 
*/

void awaitGo(int sock, char* buffer) {
	//wait logic
	recvWrap(sock, buffer, 5, Go);
}

/*
Function name: rpsGameplay
Description: 

Parameters: 
Return value: 
*/

void rpsGameplay(int sock,char* buffer) {
	printf("ROSHAMBO!\nEnter your choice here between the CAPS options: \nROCK, PAPER, SCISSORS, shoot! -> ");
	fgets(buffer, 8, stdin);
	printf("Sending to server... Awaiting response... ");

}

/*
Function name: awaitLoop
Description: 

Parameters: 
Return value: 
*/

bool awaitLoop(int sock, char* buffer) {
	bool result;
	recvDelim(sock, buffer, 0); //Problem: length doesn't match...!!!
	if(parseMessage(buffer, Go)) {
		result = false;
	}
	else if(parseMessage(buffer, Score)) {
		result = true;
	}
	else {
		//See Note 1.
	}
	return result;
}

/*
Function name: gameOverRoutine
Description: 

Parameters: 
Return value: 
*/

void gameOverRoutine(int sock, char* buffer) {
	recvWrap(sock, buffer, 7, Stop);

}

/*
Function name: main

Parameters: argc and argv pair (int and char*[] respectively) - typical arguments
Return value: int - exit status

Purpose of the client:

 - Use IP address from argument to establish communication with the server
 - Send a READY message and wait for a response (send number of turns?)
 - Prompt user for a nickname
 - Send nickname in a message and wait for a response (if READY, proceed.  if RETRY, loop back)
 - Wait for GO message first.
 - Prompt user for roshambo choice (rock, paper, scissors)
 - Send choice to server and await response of GO or a SCORE
 - If GO, loop back.  If SCORE with info, display to player
 - Await STOP message to ensure connection to server is severed
 - Terminate and alert the user to GAME OVER

*/

int main(int argc, char* argv[]) {

    //Initialize proper variables
	char buffer[MAXCHARS]; //generic use text buffer
	char nickname[MAXCHARS]; //nickname text buffer
	char ip[MAXCHARS]; //server address
	bool gameFinished = false;
	int sock; //socket identifier
	int port; //port number
	struct sockaddr_in server_addr;
	//struct sockaddr_in client_addr;

    // Check number of arguments to ensure correctness
    if (argc == 3) {
		//Copy arguments into proper variables
		strcpy(argv[1], ip);
		port = atoi(argv[2]);
    }
	else if (argc == 2) {
		//Copy arguments into proper variables
		strcpy(argv[1], ip);
		port = 1024;
	}
	else {
		//print response that displays proper usage
		printf("Proper usage: \n./client.out <ip_address> <port>\n");
        return 0;
	}

	//Ensure port is within range
	if ((port < 0) || (port > 65535)) {
		printf("Invalid port number: 0 - 65535\n");
        return 0;
	}
	
    //Sequence of events

	//Establish connection with server, then send ready message.
	if (establishConnections(ip, port, &sock, &server_addr, buffer) < 0) {
		printf("Connection not established, aborting.\n");
		return -1;
	}

	recvWrap(sock, buffer, 8, Ready);

	//Prompt user for nickname, send to server, wait for response
	nameEntry(nickname, buffer, sock);

	//Wait for Go message to be received and verified, then proceed with Roshambo
	//Game loop begins here
	awaitGo(sock, buffer);
	while(!gameFinished) {
		//rpsGameplay();
		gameFinished = awaitLoop(sock, buffer);
	}

	//Wait for a stop message to ensure connection termination, then terminate
	gameOverRoutine(sock, buffer);
	
	//terminate connection formally??  how??
	close(sock);
	printf("Well at least it compiles! \n");

	return 0;
}
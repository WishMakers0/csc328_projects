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
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <netwLib.h>

//preprocessor defines
#define MAXCHARS 256
#define NICKSIZE 24
#define NICKBUFFER 32

//enum for constants declared in place of a million preprocessor definitions
typedef enum MessageType { Ready=1, Go=2, Nick=3, Retry=4, RPS=5, Score=8, Stop=9 };

//Note 1: spit out error message and prompt for another message?
//Classic Two Generals' Problem - https://www.youtube.com/watch?v=IP-rGJKSZ3s

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
Function name: establishConnection
Description: 

Parameters: char* ip - ip address specified
			int port - port number specified
			int* socket - pointer to socket int
Return value: 
*/
void establishConnections(char* ip, int port, int* sock, struct sockaddr *server_addr, struct sockaddr_in *client_addr, char* buffer) {
	*sock = socket(AF_INET, SOCK_STREAM, 0); //establish socket file descriptor

	//create memory and initialize sockaddr
	memset(server_addr, 0, sizeof(struct sockaddr));
	server_addr->sin_family = AF_INET;
    server_addr->sin_addr.s_addr = inet_addr(ip);
    server_addr->sin_port = htons(port);

	//binds the host socket
	bind(*sock, server_addr, sizeof(struct sockaddr));
	
	//connects to server socket
	if (connect(*sock, server_addr, sizeof(struct sockaddr)) != 0) {
		//error!
		return -1;
	}

	sendDelim(*sock, "READY", 5, 0, Ready);
	printf("Connection with server successful.  Waiting for server response...");
	recvDelim(*sock, buffer, 8, 0);
	if(!parseMessage(buffer, Ready)) {
		//see Note 1
	}

}

/*
Function name: nameEntry
Description: 

Parameters: 
Return value: 
*/

void nameEntry(char* nick, char* buffer, int* sock) {
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
				printf("Display name can not contain digits, commas, or the at sign.  Try again.\n")
			}
		}

		printf("Waiting for server...");
		recvDelim(*sock, buffer, 8, 0);
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

void awaitGo(char* buffer, int* sock) {
	//wait logic
	recvDelim(*sock, buffer, 0, 5);
	if(!parseMessage(buffer, Go)) {
		//see Note 1
	}
}

/*
Function name: rpsGameplay
Description: 

Parameters: 
Return value: 
*/

void rpsGameplay() {

}

/*
Function name: awaitLoop
Description: 

Parameters: 
Return value: 
*/

bool awaitLoop(int* sock, char* buffer) {
	recvDelim(*sock, buffer, 8, 0); //Problem: length doesn't match!!!
	if(parseMessage(buffer, Go)) {
		printf("Nickname approved.  Waiting for opponent...\n");
	}
	else if(parseMessage(buffer, Stop)) {
		printf("Nickname denied - same as opponent.  Try again.\n");
	}
	else {
		//See Note 1.
	}
}

/*
Function name: finalDisplay
Description: 

Parameters: 
Return value: 
*/

void finalDisplay() {

}

/*
Function name: gameOverRoutine
Description: 

Parameters: 
Return value: 
*/

void gameOverRoutine(char* buffer) {
	//recvDelim(socket, buffer, MAXCHARS, 0);
	if(!parseMessage(buffer, Stop)) {
		//see Note 1
	}
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
	char server_addr[MAXCHARS] //server address
	bool gameFinished = false;
	int sock; //socket identifier
	int port; //port number
	struct sockaddr server_addr
	struct sockaddr_in client_addr;

    // Check number of arguments to ensure correctness
    if (argc != 3) {
        //print response that displays proper usage
        return 0;
    }
	
	//Copy arguments into proper variables
	strcpy(argv[1], server_addr);
	port = atoi(argv[2]);

    //Sequence of events

	//Establish connection with server, then send ready message.
	//establishConnection(server_addr, port, &sock);

	//Wait for a response back from the server, then verify it.
	//recvDelim(socket, buffer, MAXCHARS, 0);
	if(!parseMessage(buffer, Ready)) {
		//see Note 1
	}

	//Prompt user for nickname, send to server, wait for response
	//nameEntry();

	//Wait for Go message to be received and verified, then proceed with Roshambo
	//Game loop begins here
	awaitGo(buffer);
	while(!gameFinished) {
		//rpsGameplay();
		//gameFinished = awaitLoop(&gameFinished);
	}

	//Wait for a stop message to ensure connection termination, then terminate
	gameOverRoutine(buffer);
	
	//terminate connection formally??  how??

	return 0;
}
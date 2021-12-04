/*
	Author: Daniel Oravetz
	Major: Computer Science
	Creation Date: November 30, 2021
	Due Date: December 3, 2021
	Course: CSC328-010
	Professor Name: Dr. Frye
	Assignment: RPS Project - Client Portion
	Filename: client.c
	Purpose: Act as a client to a client-server based Rock Paper Scissors game.
			See comment on main for further implementation details.

	Run command: ./client.out <ip_address> <port num*>
			*optional argument, defaults to 1024
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
#include <netdb.h>
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
Description: Displays score to the user after Score packet is received

Parameters: char* buffer - string buffer to display
Return value: N/A
*/
void finalDisplay(char* buffer) {
	//Process copy buffer from processed message to display final score results.
	//example packet: SCORE ?????
	printf("Display placeholder because who the [EXPLETIVE] knows what the Score packets look like yet. \n");
}

/*
Function name: getTrueMessageLength
Description: Gets the substring of a packet received from a server, removing the header and delimiter
			(Fun fact: the version used in server.c's "substr" function is just a more elegant version of this and what is done in parseMessage.)
			(Doubly fun fact: it works so well that I'll just replace this function with that one altogether.)
Parameters: char* buffer - the received full message

Return value: int length - the length of the "true" message within an encoded packet


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
}*/

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

/*
Function name: parseMessage
Description: Handles any received packet from the server and parses it to perform the appropriate action.
			For most packet types, all it needs to do is verify the packet matches the expected result.
			For others like Score packets, it provides the way for the message to be displayed to the screen.

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
	//int messageLength = getTrueMessageLength(buffer);
	//strncpy(copyBuffer, &buffer[2], messageLength);
	int messageLength = strsub(buffer, copyBuffer);

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
	recvFinal(sock, buffer, 0);
	if(!parseMessage(buffer, type)) {
		//see Note 1
	}
}


/*
Function name: hostnameIpConvert
Description: Converts hostname of website to an IP.  (Oh, we need to do this, I was just going to use an IP when testing...)

Parameters: char* buffer - ip address buffer
			int sock - socket file descriptor
			struct sockaddr_in* server_addr - socket server address information
Return value: N/A
*/
void hostnameIpConvert(char* buffer, int sock, struct sockaddr_in* server_addr) {
	struct addrinfo hints, *res, *it;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(buffer, "http", &hints, &res) != 0) {
		//error message?
	}

	//for(it = res; it != NULL, it=it->ai_next) {}
	struct sockaddr_in* temp = (struct sockaddr_in*) res->ai_addr;
	server_addr->sin_addr = temp->sin_addr;
	//get first IP address and place it in server_addr

	freeaddrinfo(res); //free this structure
}

/*
Function name: establishConnection
Description: The first part of the client process, creates the socket, connects, and sends the first READY message to the server.

Parameters: char* ip - hostname specified (previously ip address!)
			int port - port number specified
			int* socket - pointer to socket file descriptor
			struct sockaddr_in* server_addr - socket server address information
			char* buffer - generic string buffer
Return value: int - status of connection, -1 if failed, 0 if success
*/
int establishConnections(char* ip, int port, int* sock, struct sockaddr_in* server_addr, char* buffer) {
	*sock = socket(AF_INET, SOCK_STREAM, 0); //establish socket file descriptor

	//create memory and initialize sockaddr
	memset(server_addr, 0, sizeof(struct sockaddr));
	server_addr->sin_family = AF_INET;
	hostnameIpConvert(ip, *sock, server_addr); //convert hostname to IP address
	//inet_aton(ip, server_addr->sin_addr.s_addr); //use with only an ip address!!
    server_addr->sin_port = htons(port);

	//binds the host socket
	//bind(*sock, (struct sockaddr*)server_addr, sizeof(struct sockaddr_in));
	
	//connects to server socket
	if (connect(*sock, (struct sockaddr*)server_addr, sizeof(struct sockaddr_in)) != 0) {
		//error connecting to server!
		printf("Couldn't connect to server, aborting. \n");
		return -1;
	}

	sendDelim(*sock, "READY", 5, 0, Ready);
	//printf("Connection with server successful.  Waiting for server response...");
	//recvWrap(*sock, buffer, 8, Ready);
	return 0;
}

/*
Function name: nameEntry
Description: Second major part of the client process, handling nickname entry.
			Ensures proper ranges for character length, and handles banned characters (ones used in packet processing).
Parameters: char* nick - nickname buffer
			char* buffer - general string buffer
			int sock - socket file descriptor
Return value: N/A
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
		//blocking fxn here necessary?  probably not.
		recvFinal(sock, buffer, 0);
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
Function name: rpsGameplay
Description: Third major part of the client - the actual RPS inputs from the user
			Verifies that the string input is "close enough" to ROCK, PAPER, or SCISSORS and sets it to a valid value.
			Sends the packet to the server afterward.
Parameters: int sock - socket file descriptor
			char* buffer - generic string buffer
Return value: N/A
*/

void rpsGameplay(int sock,char* buffer) {
	bool valid = false; 
	char choice[9];
	memset(&choice[0], 0, 9); //clear choice buffer
	while(!valid) {
		printf("ROSHAMBO!\nEnter your choice here between the CAPS options: \nROCK, PAPER, SCISSORS, shoot! -> ");
		fgets(buffer, 9, stdin);
		switch(buffer[0]) {
			//I did not care enough to use strcmp for this...
			case('R'):
				strcpy(choice, "ROCK");
				valid = true;
				printf("ROCK chosen! \n");
			case('S'):
				strcpy(choice, "SCISSORS");
				valid = true;
				printf("SCISSORS chosen! \n");
				break;
			case('P'):
				strcpy(choice, "PAPER");
				valid = true;
				printf("PAPER chosen! \n");
				break;
			case('r'):
				strcpy(choice, "ROCK");
				valid = true;
				printf("ROCK chosen! \n");
			case('s'):
				strcpy(choice, "SCISSORS");
				valid = true;
				printf("SCISSORS chosen! \n");
				break;
			case('p'):
				strcpy(choice, "PAPER");
				valid = true;
				printf("PAPER chosen! \n");
				break;
			default:
				printf("Invalid entry, try again. \n");
				break;
		}
	}
	printf("Sending to server... Awaiting response... ");
	sendDelim(sock, buffer, 8, 0, RPS);
}

/*
Function name: awaitLoop
Description: Other part of RPS gameplay, waits for a packet from the server and evaluates whether to continue game loop or stop,
			based on the resulting packet.
Parameters: int sock - socket file descriptor
			char* buffer - generic string buffer
Return value: bool - true to continue looping, false to break loop
*/

bool awaitLoop(int sock, char* buffer) {
	bool result;
	recvFinal(sock, buffer, 0); //Problem: length doesn't match...!!!
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
Description: Final part of client.  Receives Stop packet from server and closes socket.

Parameters: int sock - socket file descriptor
			char* buffer - generic string buffer
Return value: N/A
*/

void gameOverRoutine(int sock, char* buffer) {
	recvWrap(sock, buffer, 7, Stop);
	//terminate connection formally
	close(sock);
	printf("Connection with server finished, terminating. \n");
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
	recvWrap(sock, buffer, 5, Go);
	while(!gameFinished) {
		rpsGameplay(sock, buffer);
		gameFinished = awaitLoop(sock, buffer);
	}

	//Wait for a stop message to ensure connection termination, then terminate
	gameOverRoutine(sock, buffer);

	//printf("Well at least it compiles! \n");

	return 0;
}
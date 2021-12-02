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

//enum for constants declared in place of a million preprocessor definitions
typedef enum MessageType { Ready=1, Go=2, Nick=3, Retry=4, RPS=5, Score=8, Stop=9 };

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
Return value: 
*/
void establishConnection(char* ip, int port) {

}

/*
Function name: nameEntry
Description: 

Parameters: 
Return value: 
*/

void nameEntry() {
	//Obvious note to future self: when parsing nickname options PLEASE make sure there aren't any digits, commas, or at signs
}

/*
Function name: awaitGo
Description: 

Parameters: 
Return value: 
*/

void awaitGo(char* buffer) {
	//recvDelim(socket, buffer, MAXCHARS, 0);
	if(!parseMessage(buffer, Go)) {
		//spit out error message and prompt for another message?
		//Classic Two Generals' Problem - https://www.youtube.com/watch?v=IP-rGJKSZ3s
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

void awaitLoop() {

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
		//spit out error message and prompt for another message?
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
	bool gameFinished = false;
	int socket; //socket???

    // Check number of arguments to ensure correctness
    if (argc != 3) {
        //print response that displays proper usage
        return 0;
    }

    //Sequence of events

	//Establish connection with server, then send ready message.
	//establishConnection();

	//Wait for a response back from the server, then verify it.
	//recvDelim(socket, buffer, MAXCHARS, 0);
	if(!parseMessage(buffer, Ready)) {
		//spit out error message and prompt for another message?
		//Classic Two Generals' Problem - https://www.youtube.com/watch?v=IP-rGJKSZ3s
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
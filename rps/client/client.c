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

	Run command: ./client.out <arguments>
	Compile command: 
		make build_client
        *OR*
        make build_all

	<end>
*/

/*
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
*/



/*
Function name: establishConnection
Description: 

Parameters: 
Return value: 
*/
void establishConnection() {

}

/*
Function name: nameEntry
Description: 

Parameters: 
Return value: 
*/

void nameEntry() {

}

/*
Function name: awaitGo
Description: 

Parameters: 
Return value: 
*/

void awaitGo() {

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

void gameOverRoutine() {

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
 - Send GO message to server, do not wait for a response back
 - Prompt user for roshambo choice (rock, paper, scissors)
 - Send choice to server and await response of GO or a SCORE
 - If GO, loop back.  If SCORE with info, display to player
 - Await STOP message to ensure connection to server is severed
 - Terminate and alert the user to GAME OVER

*/

int main(int argc, char* argv[]) {

    //Initialize proper variables

    // Check number of arguments to ensure correctness
    if (argc != 3) {
        //print response that displays proper usage
        return 0;
    }

    //Sequence

}
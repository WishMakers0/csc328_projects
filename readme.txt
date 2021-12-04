ID block
Author:           Kamal Sheets                   
Major:            Computer Science              
Creation Date:    November 27 2021              
Due Date:         December 2 2021               
Course:           CSC 328                       
Professor:        Dr. Frye                      
Assignment:       RPS - Server                  
Filename:         Server.c                      
Language:		      C                 
Version:		      8.3.0            

How to build and run the client and server
run make <keyword>
build_server build_client build_all

File/folder manifest identifying the purpose of each file/folder included in the project


Responsibility matrix – table containing a row for each team member and the aspects of
the project to which they contributed

Boyd Lenich   Client
Dan Oravetz   Server
Kamal Sheets  Readme and Library

Application Protocol – the details of your developed protocol, including the initial protocol
defined above, and the protocol for socket reads/writes

Protocol: reads / writes have a beginning , then a number detailing the type of message, then after the message an @ sign to denote and end of message delimiter.
1 - READY
2 - GO
3 - <nickname>
4 - RETRY
5 - RPS (can be ROCK, PAPER, or SCISSORS for the data segment and be valid)
6,7 - (reserved as we have no use for them, fall through and treat like READY or some other default behavior)
8 - SCORE
9 - STOP

Assumptions – clearly list and describe any assumptions made about running the
application or how the application works

Assumes nicknames is less than 32 bytes.

Discussion on your development process, including any decisions and/or major problems
you encountered and your solution for each

major problems with pipes and socket connections, specifically with pointers and how they work in client.

Status – current status of applications in terms of specifications, and any known issues
with the application (things that don’t work or any idiosyncrasies). 

Nonfunctional: Errors within client due to pipes.

#written by Dan Oravetz for the RPS project

CLIENT_SRC = ./client/client.c 
LIBRARY_SRC = ./libraries/Library.c ./libraries/Library.h
SERVER_SRC = ./server/server.c 

#we need to decide whether we're using static or dynamic libraries
build_client: $(CLIENT_SRC) $(LIBRARY_SRC)
	make build_libraries_static
	gcc -c ./client/client.c -Ilibraries -g
	mv client.o ./obj/client.o
	gcc -static -o client.out ./obj/client.o -L. -lLibrary -g
	mv client.out ./bin/client.out
	make cleanup_objects

build_server: $(SERVER_SRC) $(LIBRARY_SRC)
	make build_libraries_static
	gcc -c ./server/server.c -Ilibraries -g
	mv server.o ./obj/server.o
	gcc -static -o server.out ./obj/server.o -L. -lLibrary -g
	mv server.out ./bin/server.out
	make cleanup_objects

build_all: $(CLIENT_SRC) $(SERVER_SRC) $(LIBRARY_SRC)
	make build_client
	make build_server 

#don't use this one yourself, use build_client, build_server, or build_both
build_libraries_static: $(LIBRARY_SRC)
	gcc -c ./libraries/Library.c
	mv ./Library.o ./obj/Library.o
	ar rc libLibrary.a ./obj/*.o 
	make cleanup_objects;

#don't use this one yourself, use build_client, build_server, or build_both
#build_libraries_dynamic: $(LIBRARY_SRC)
#	mkdir bin
#	mkdir obj
#	cd obj
#	gcc -fpic -c ./../libraries/*.c 
#	cd ..
#	cd bin
#	gcc -shared -o netwLib.so ./../obj/*.o 

#used by library building after completed
cleanup_objects: 
	rm ./obj/*.o 

remove:
	rm ./bin/*.out
	rm ./*.a
	rm ./*.so
	make cleanup_objects

#done 


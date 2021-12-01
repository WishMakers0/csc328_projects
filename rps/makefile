#written by Dan Oravetz for the RPS project

CLIENT_SRC = ./client/client.c 
LIBRARY_SRC = ./libraries/Library.c 
SERVER_SRC = ./server/server.c #placeholder

#we need to decide whether we're using static or dynamic libraries
build_client: $(CLIENT_SRC) $(LIBRARY_SRC)
	gcc -c 

build_server: $(SERVER_SRC) $(LIBRARY_SRC)
	gcc -c 

build_all: $(CLIENT_SRC) $(SERVER_SRC) $(LIBRARY_SRC)
	make build_client
	make build_server 

#don't use this one yourself, use build_client, build_server, or build_both
build_libraries_static: $(LIBRARY_SRC)
	mkdir bin 
	mkdir obj
	cd obj
	gcc -c ./../libraries/*.c
	cd ..
	cd bin
	ar rc netwLib.a ./../obj/*.o 

#don't use this one yourself, use build_client, build_server, or build_both
build_libraries_dynamic: $(LIBRARY_SRC)
	mkdir bin
	mkdir obj
	cd obj
	gcc -fpic -c ./../libraries/*.c 
	cd ..
	cd bin
	gcc -shared -o netwLib.so ./../obj/*.o 

#used by library building after completed
cleanup_objects: 
	rm ./obj/*.o 

remove:
	rm ./bin/*.out ./bin/*.a ./bin/*.so ./bin/*.o
	make cleanup_library

#done 


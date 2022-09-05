CC  = gcc
CXX = g++
INC = include
LIB = lib
SRC = src
STD = -std=c++20
OBJ_1 = dlfunctions.o
OBJ_2 = $(LIB)/libdlfunc.so
OBJ_3 = dynamicload.o $(OBJ_1) 
OBJ_4 = $(LIB)/libdload.so

CFLAGS = -fpic -I$(INC) -c
LFLAGS = -shared -I$(INC) -o

build:
	@echo CC  Building dlfunctions ...
	$(CC) $(CFLAGS) $(SRC)/dlfunctions.c
	$(CC) $(LFLAGS) $(OBJ_2) $(OBJ_1)
	@echo
	@echo CXX Building dynamicload ...
	$(CXX) $(STD) $(CFLAGS) $(SRC)/dynamicload.cxx 
	$(CXX) $(STD) $(LFLAGS) $(OBJ_4) $(OBJ_3)
	@echo
	@echo Done ^,..,^

install:
	@echo Installing dynamicload ...
	@sudo cp $(LIB)/*.so /usr/lib
	@sudo cp $(INC)/* /usr/include
	@echo Configuring LD ...
	@sudo ldconfig
	@echo Done ^,..,^

remove:
	@echo Uninstalling dynamicload ...
	@sudo rm /usr/lib/libdlfunc.so /usr/lib/libdload.so
	@sudo rm /usr/include/dlconfiguration.hxx /usr/include/dlexception.hxx /usr/include/dlfunctions.h /usr/include/dynamicload.hxx
	@sudo ldconfig
	@echo Done ^,..,^

clean:
	@echo Cleaning up risidual files ...
	@rm *.o && rm lib/*.so
	@echo Done ^,..,^


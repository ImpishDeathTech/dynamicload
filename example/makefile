CC  = gcc
CXX = g++
LIB = ../lib
INC = ../include
STD = -std=c++20

LIB_CFLAGS = -fpic -I$(INC) -L$(LIB) -c
LIB_LFLAGS = -shared -I$(INC) -L$(LIB) -o

CFLAGS     = -I$(INC) -L$(LIB) -c
LFLAGS     = -I$(INC) -L$(LIB) -o

SRC_1 = test1
SRC_2 = test2
SRC_3 = test3
SRC_4 = testlib1
SRC_5 = testlib2

OBJ_1 = $(SRC_1).out
OBJ_2 = $(SRC_2).out
OBJ_3 = $(SRC_3).out
OBJ_4 = libtest1.so
OBJ_5 = libtest2.so

run:
	@echo Buildingg test1 ...
	$(CC) $(CFLAGS) $(SRC_1).c
	$(CC) $(LFLAGS) $(OBJ_1) $(SRC_1).o -ldlfunc 
	@echo
	@echo Building test2 ...
	$(CXX) $(STD) $(CFLAGS) $(SRC_2).cxx
	$(CXX) $(STD) $(LFLAGS) $(OBJ_2) $(SRC_2).o -ldload
	@echo
	@echo Buildingg test3 ...
	$(CXX) $(STD) $(CFLAGS) $(SRC_3).cxx
	$(CXX) $(STD) $(LFLAGS) $(OBJ_3) $(SRC_3).o -ldload
	@echo
	@echo Building testlib ...
	$(CC) $(LIB_CFLAGS) $(SRC_4).c
	$(CC) $(LIB_LFLAGS) $(OBJ_4) $(SRC_4).o -ldlfunc
	@echo
	@echo Running tests ...
	@echo
	./$(OBJ_1) ./$(OBJ_4) testprint "Hello, world! ^,..,^"
	@echo
	./$(OBJ_2) ./$(OBJ_4) testtrunc 2354.563456
	@echo
	./$(OBJ_3) ./$(OBJ_4) testprint "Hello, world! ^,..,^" testprintint testtrunc 666.3465
	@echo
	
clean:
	@echo Cleaning up risidual files ...
	@rm *.o *.out *.so

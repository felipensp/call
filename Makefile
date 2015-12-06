CC?=clang

PROGRAM=call
SRC=src
BLD=build
INC=include
OBJS=$(BLD)/*.o
INSTALLBIN=/usr/bin

call: $(SRC)/*.c $(INC)/*.h
	mkdir -p $(BLD)
	$(CXX) -fPIC -g -ggdb -c -Wall -std=c++11 -I$(INC)/ -o$(BLD)/loader.o $(SRC)/loader.c
	$(CXX) -fPIC -g -ggdb -c -Wall -std=c++11 -I$(INC)/ -o$(BLD)/caller.o $(SRC)/caller.c
	$(CXX) -fPIC -g -ggdb -c -Wall -std=c++11 -I$(INC)/ -o$(BLD)/main.o $(SRC)/main.c

	$(CXX) -o$(PROGRAM) $(OBJS) -ldl

clean:
	rm -rf $(PROGRAM) $(OBJS)

install:
	$(CXX) -o$(INSTALLBIN)/$(PROGRAM) $(SRC)/main.c

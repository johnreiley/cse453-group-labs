###############################################################
# Program:
#     W12-Bell-LaPadula
#     Brother Wilson, CSE435
# Author:
#     Benjamin Hansen
###############################################################

LFLAGS = -lglut -lGLU -lGL

###############################################################
# Build the main game
###############################################################
a.out: lab12.o interact.o messages.o message.o unit-tests.o control.o
	g++ lab12.o interact.o messages.o message.o unit-tests.o control.o $(LFLAGS)

lab12.o: lab12.cpp interact.h messages.h message.h control.h unit-tests.h
	g++ -c lab12.cpp

control.o: control.h control.cpp
	g++ -c control.cpp

interact.o: interact.h messages.h control.h interact.cpp
	g++ -c interact.cpp

messages.o: messages.h message.h control.h messages.cpp
	g++ -c messages.cpp

message.o: message.h control.h message.cpp
	g++ -c message.cpp

unit-tests.o: unit-tests.h interact.h messages.h message.h control.h unit-tests.cpp
	g++ -c unit-tests.cpp

###############################################################
# General rules
###############################################################
clean:
	rm a.out *.o

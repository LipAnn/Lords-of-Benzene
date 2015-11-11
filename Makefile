OBJECTS=NeuralDetector.o InputProcessor.o
CC=g++
CFLAGS= -std=gnu++11 `pkg-config opencv --cflags` -O2
CLIBS=`pkg-config opencv --libs`
all : main
main : $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(CLIBS) -o $@
NeuralDetector.o : NeuralDetector.cpp InputProcessor.h NeuralDetector.h ImagePack_t.h
	$(CC) $(CFLAGS) -c $< $(CLIBS) -o $@
InputProcessor.o : InputProcessor.cpp InputProcessor.h ImagePack_t.h
	$(CC) $(CFLAGS) -c $< $(CLIBS) -o $@
clean :
	rm -f *.o main

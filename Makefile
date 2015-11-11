OBJECTS=NeuralDetector.o InputProcessor.o SamplesGenerator.o NeuralYoda.o
CC=g++
CFLAGS= -std=gnu++11 `pkg-config opencv --cflags` -O2
CLIBS=`pkg-config opencv --libs`
all : main
main : $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(CLIBS) -o $@
NeuralDetector.o : NeuralDetector.cpp InputProcessor.h NeuralDetector.h CommonHeader.h
	$(CC) $(CFLAGS) -c $< $(CLIBS) -o $@
InputProcessor.o : InputProcessor.cpp InputProcessor.h CommonHeader.h
	$(CC) $(CFLAGS) -c $< $(CLIBS) -o $@
SamplesGenerator.o : SamplesGenerator.cpp CommonHeader.h SamplesGenerator.h
	$(CC) $(CFLAGS) -c $< $(CLIBS) -o $@
NeuralYoda.o : NeuralYoda.cpp NeuralYoda.h
	$(CC) $(CFLAGS) -c $< $(CLIBS) -o $@
clean :
	rm -f *.o main

OBJECTS=Manager.o main.o NeuralDetector.o InputProcessor.o Spokesman.o
CC=g++
CFLAGS= -std=gnu++11 `pkg-config opencv --cflags` -O2
CLIBS=`pkg-config opencv --libs` -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann -lopencv_nonfree
all : main
main : $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(CLIBS) -o $@
Manager.o : Manager.cpp Manager.h
	$(CC) $(CFLAGS) -c $< $(CLIBS) -o $@
main.o : main.cpp Manager.h
	$(CC) $(CFLAGS) -c $< $(CLIBS) -o $@
NeuralDetector.o : NeuralDetector.cpp InputProcessor.h NeuralDetector.h CommonHeader.h
	$(CC) $(CFLAGS) -c $< $(CLIBS) -o $@
InputProcessor.o : InputProcessor.cpp InputProcessor.h CommonHeader.h
	$(CC) $(CFLAGS) -c $< $(CLIBS) -o $@
Spokesman.o : Spokesman.cpp Spokesman.h
	$(CC) $(CFLAGS) -c $< $(CLIBS) -o $@
clean :
	rm -f *.o main

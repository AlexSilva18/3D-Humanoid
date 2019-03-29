COMPILER = g++
#FLAGS = -lGLEW -lglfw -lassimp -lGL -lX11 -lpthread -lXrandr -ldl -lXxf86vm -lXinerama -lXcursor -lrt -lm -std=c++11 -I /usr/include/SOIL -lSOIL
FLAGS = -std=c++11 main.cpp -g -lglfw -lGL -lGLEW -lassimp -lpthread
CLIENT_FILES = main.cpp

default: model

model: $(CLIENT_FILES) 
	$(COMPILER) $(FLAGS) -o mod

clean:
	rm -rf *~ *.o .*.swp "#*.c#" mod

runmod:
	./mod

#	#$(COMPILER) -O3 $(CLIENT_FILES) -o model $(FLAGS)

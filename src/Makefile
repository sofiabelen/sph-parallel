CC=g++

FLAGS=
# FLAGS= -fopenmp

all: sph

sph: main.o input.o grid.o output.o
	$(CC) $(FLAGS) main.o input.o grid.o output.o

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

input.o: input.cpp
	$(CC) $(FLAGS) -c input.cpp

output.o: output.cpp
	$(CC) $(FLAGS) -c output.cpp

grid.o: grid.cpp
	$(CC) $(FLAGS) -c grid.cpp

clean:
	rm *.o a.out


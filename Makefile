OBJ= Main.o ArrayMap.o
OPTS= -g -c -Wall -Werror

Prog3: $(OBJ)
	g++ -o ArrayMap $(OBJ)

Main.o: main.cpp ArrayMap.h ArrayMap.cpp
	g++ $(OPTS) main.cpp

ArrayMap.o: ArrayMap.cpp ArrayMap.h
	g++ $(OPTS) ArrayMap.cpp

clean:
	rm -f *.o *~ *#
CC= g++ -g
CFLAGS= 
DEPS = reverseDelete.h
OBJ = reverseDelete.o main.o 
EXE = final

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ)
	g++ -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o *~ core $(EXE)

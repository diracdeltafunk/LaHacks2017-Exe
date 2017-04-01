CC=clang++
CFLAGS=-O2 -std=c++14
DEPS = expression.h
OBJ = main.o expression.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~

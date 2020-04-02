output: kunde.o uebung9_4.o
	clang kunde.o uebung9_4.o -o output

kunde.o: kunde.c kunde.h
	clang -c kunde.c

uebung9_4.o: uebung9_4.c
	clang -c uebung9_4.c

clean:
	rm *.o output

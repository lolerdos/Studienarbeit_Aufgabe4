CC      = cl
LINK    = link
LIB     = lib
INCLPATH= "__________"
COMPOPT  = -I$ (INCLPATH) -c
LINKOPT = /LIBPATH: "__________" 
LIBOUT  = /OUT:

all: uebung9_4.exe

kunde.o: kunde.c kunde.h
	$(CC) $(COMPOPT) kunde.c

uebung9_4.o: uebung9_4.c
	$(CC) $(COMPOPT) uebung9_4.c
	
kunde.lib: kunde.obj
	$(LIB) $(LINKOPT) kunde.obj $(LIBOUT) kunde.lib
	
uebung9_4.exe: kunde.lib uebung9_4.obj
	 $(LINK) $(LINKOPT) kunde.lib uebung9_4.obj




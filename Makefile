PROG = main.exe 
SRC = main.c menu.c printcards.c remoteopen.c fileConfig.c
CFLAGS=-Wall -Werror -g
LIBS = 
all: $(PROG)
$(PROG): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRC)  $(LIBS) 
clean:
	rm -f $(PROG)
.PHONY: all clean
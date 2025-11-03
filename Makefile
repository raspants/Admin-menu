PROG = main.exe 
SRC = main.c menu.c printcards.c remoteopen.c fileHandeling.c addRemoveAcces.c cardScan.c safeinput.c clearCls.c timeDelay.c
CFLAGS=-Wall -Werror -g
LIBS = 
all: $(PROG)
$(PROG): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRC)  $(LIBS) 
clean:
	rm -f $(PROG)
.PHONY: all clean
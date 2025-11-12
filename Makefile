PROG = main.exe 

DEPS=includes/*.h
SOURCES = main.c menu.c printcards.c remoteopen.c fileHandeling.c addRemoveAcces.c cardScan.c safeinput.c clearCls.c timeDelay.c

CFLAGS=-Wall -Werror -g -Iincludes
LIBS = 
OUTPUTDIR=obj
OBJS = $(addprefix $(OUTPUTDIR)/, $(SOURCES:.c=.o))

all: $(OUTPUTDIR) $(PROG)

$(PROG): $(OBJS) 
	$(CC) -o $@ $^ $(CFLAGS)

$(OUTPUTDIR)/%.o : src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTPUTDIR):
	@mkdir "$(OUTPUTDIR)"

clean:
	@del /q "$(OUTPUTDIR)" 
	@del /q $(PROG)


.PHONY: prep clean
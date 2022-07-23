.SUFFIXES:
.SUFFIXES: .c .o
CC = clang
CFLAGS = -Wall -Wextra
LFLAGS = -lSDL2

ODIR = obj
BDIR = ../bin

_OBJ = main.o back.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

DEP = back.h

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

game: $(OBJ)
	# $(CC) -o $(BDIR)/$@ $^ $(CFLAGS) $(LFLAGS)
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)

.SUFFIXES:
.SUFFIXES: .c .o
CC = clang
CFLAGS = -Wall -Wextra
LFLAGS = -lSDL2 -lSDL2_gfx

ODIR = obj
BDIR = ../bin

_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEP)
	$(CC) -c -o $@ $< $(CFLAGS)

run: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)

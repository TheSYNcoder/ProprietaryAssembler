IDIR=include
CC=gcc
CFLAGS=-I$(IDIR)
SRC=src
ODIR=build
# LDIR=../lib
# LIBS=-lm


$(ODIR)/%.o: $(SRC)/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

SOURCE=$(wildcard $(SRC)/*.c)
OBJECTS=$(patsubst $(SRC)/%.c, $(ODIR)/%.o, $(SOURCE))
$(info OBJECTS is $(OBJECTS))
# shell: $(OBJECTS)
# pasm : $(ODIR)/%.o
pasm: $(OBJECTS) 
	$(CC) -o $@ $^ $(CFLAGS)

object_test: test
	od -t x1 -A n file.obj

ld:	src/ld_lib.c include/ld_lib.h ld.c
	$(CC) -c src/ld_lib.c -o ld_lib.o -I $(IDIR)
	$(CC) ld.c ld_lib.o -o ld -I $(IDIR)
	rm -f ld_lib.o

%.exe:
	od -t x1 -A n $@

# ~ means to ignore all the warings if file is not present

.PHONY: clean

clean:
	rm -rf -f $(ODIR)
	rm -f pasm
	rm -f ld
	# rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

test: clean pasm ld
	./pasm file.pasm file.obj
	./ld file.obj file.exe
	dosbox file.exe



IDIR=include
CC=gcc
CFLAGS=-I$(IDIR)
SRC=src
ODIR=build
# LDIR =../lib
# LIBS=-lm


$(ODIR)/%.o: $(SRC)/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

SOURCE = $(wildcard $(SRC)/*.c)
OBJECTS=$(patsubst $(SRC)/%.c, $(ODIR)/%.o, $(SOURCE))
$(info    OBJECTS is $(OBJECTS))
# shell: $(OBJECTS)
# pasm : $(ODIR)/%.o
pasm : $(OBJECTS) 
	$(CC) -o $@ $^ $(CFLAGS)



# ~ means to ignore all the warings if file is not present

object_test: src/object_code.c object_test.c 
	$(CC) -c src/object_code.c -o object_code.o -I $(IDIR)
	$(CC) object_test.c object_code.o -o object_test -I $(IDIR)
	rm -f object_code.o
	./object_test
	od -t x1 -A n main.obj
	rm -f object_test

ld:	src/ld_lib.c include/ld_lib.h ld.c
	$(CC) -c src/ld_lib.c -o ld_lib.o -I $(IDIR)
	$(CC) ld.c ld_lib.o -o ld -I $(IDIR)
	rm -f ld_lib.o

%.exe:
	od -t x1 -A n $@

.PHONY: clean

clean:
	rm -rf $(ODIR)
	rm pasm
	# rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
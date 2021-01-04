IDIR =include
CC=gcc
CFLAGS=-I$(IDIR)
SRC=src
ODIR=build
# LDIR =../lib
# LIBS=-lm


$(ODIR)/%.o: $(SRC)/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@



# shell: $(OBJECTS)
pasm : $(ODIR)/main.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

# ~ means to ignore all the warings if file is not present

clean:
	rm -rf $(ODIR)
	# rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
CC=gcc
CFLAGS= -g
DFLAGS=
PROGS= typing_word_game

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $< -o typing_word_game

clean:
	rm -f $(PROGS) *.o ~*

CC=g++
CFLAGS=-Wall -std=c++14 -o3
BINS=trabajo
all: clean trabajo

lista:
	$(CC) $(CFLAGS) -o trabajo trabajo.cpp

clean:
	@echo " [CLN] Removing binary files"
	@rm -f $(BINS)


# Makefile to build the assignment 1
# by Izhar Shaikh

# Add the new TARGETS here
TARGETS = stringPoolTestApp eventListTestApp stringProcessingTestApp
CC = gcc
HEADERS = -I.
BIN_PATH = bin
CFLAGS = -Wall -g -std=c99 -Werror

all: clean create_bin $(TARGETS)

#$(TARGETS):
#	$(CC) $(CFLAGS) $@.c stringPool.c $(HEADERS) -o $(BIN_PATH)/$@

calenderFilter:
	$(CC) $(CFLAGS) $@.c $(HEADERS) -o $(BIN_PATH)/$@

stringPoolTestApp:
	$(CC) $(CFLAGS) stringPoolTestApp.c stringPool.c $(HEADERS) -o $(BIN_PATH)/$@

eventListTestApp:
	$(CC) $(CFLAGS) eventListTestApp.c eventList.c stringProcessing.c $(HEADERS) -o $(BIN_PATH)/$@

stringProcessingTestApp:
	$(CC) $(CFLAGS) stringProcessingTestApp.c eventList.c stringProcessing.c $(HEADERS) -o $(BIN_PATH)/$@

clean:
	rm -rf $(TARGETS) $(BIN_PATH) *.o

create_bin:
	mkdir $(BIN_PATH)

# Makefile to build the assignment 1
# by Izhar Shaikh

# Add the new TARGETS here
TARGETS = calenderFilter stringPoolTestApp eventListTestApp stringProcessingTestApp
CC = gcc
HEADERS = -I.
BIN_PATH = bin
CFLAGS = -Wall -std=c99 -Werror -g -O0

all: clean create_bin $(TARGETS)

#$(TARGETS):
#	$(CC) $(CFLAGS) $@.c stringPool.c $(HEADERS) -o $(BIN_PATH)/$@

calenderFilter:
	$(CC) $(CFLAGS) stringPool.c eventList.c eventProcessing.c stringProcessing.c \
	$@.c $(HEADERS) -o $(BIN_PATH)/$@

stringPoolTestApp:
	$(CC) $(CFLAGS) test_apps/stringPoolTestApp.c stringPool.c eventList.c \
	eventProcessing.c stringProcessing.c $(HEADERS) -o $(BIN_PATH)/$@

eventListTestApp:
	$(CC) $(CFLAGS) test_apps/eventListTestApp.c eventList.c stringProcessing.c \
	eventProcessing.c $(HEADERS) -o $(BIN_PATH)/$@

stringProcessingTestApp:
	$(CC) $(CFLAGS) test_apps/stringProcessingTestApp.c eventList.c stringProcessing.c \
	eventProcessing.c $(HEADERS) -o $(BIN_PATH)/$@

clean:
	rm -rf $(TARGETS) $(BIN_PATH) *.o

create_bin:
	mkdir $(BIN_PATH)

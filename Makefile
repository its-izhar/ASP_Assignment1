# @Author: Izhar Shaikh <izhar>
# @Date:   2017-02-22T17:44:29-05:00
# @Email:  izharits@gmail.com
# @Filename: Makefile
# @Last modified by:   izhar
# @Last modified time: 2017-03-06T17:06:42-05:00
# @License: MIT



# Makefile to build the assignment 1
# by Izhar Shaikh

# Add the new TARGETS here
TARGETS = calenderFilter stringPoolTestApp eventListTestApp stringProcessingTestApp \
					stringProcessingTestApp2 eventListTestApp2 emailFilter calenderUpdater
CC = gcc
HEADERS = -I.
BIN_PATH = bin
CFLAGS = -Wall -Werror -std=c99 -O2 #-g -DDEBUG

all: clean create_bin $(TARGETS)

#$(TARGETS):
#	$(CC) $(CFLAGS) $@.c stringPool.c $(HEADERS) -o $(BIN_PATH)/$@
calenderUpdater:
	$(CC) $(CFLAGS) calenderUpdater.c $(HEADERS) -o $(BIN_PATH)/$@

emailFilter:
	$(CC) $(CFLAGS) emailFilter.c stringPool.c eventList.c eventProcessing.c \
	stringProcessing.c $(HEADERS) -o $(BIN_PATH)/$@

calenderFilter:
	$(CC) $(CFLAGS) stringPool.c eventList.c eventProcessing.c stringProcessing.c \
	$@.c $(HEADERS) -o $(BIN_PATH)/$@

stringPoolTestApp:
	$(CC) $(CFLAGS) test_apps/stringPoolTestApp.c stringPool.c eventList.c \
	eventProcessing.c stringProcessing.c $(HEADERS) -o $(BIN_PATH)/$@

eventListTestApp:
	$(CC) $(CFLAGS) test_apps/eventListTestApp.c eventList.c stringProcessing.c \
	eventProcessing.c $(HEADERS) -o $(BIN_PATH)/$@

eventListTestApp2:
	$(CC) $(CFLAGS) test_apps/eventListTestApp2.c eventList.c stringProcessing.c \
	eventProcessing.c $(HEADERS) -o $(BIN_PATH)/$@

stringProcessingTestApp:
	$(CC) $(CFLAGS) test_apps/stringProcessingTestApp.c eventList.c stringProcessing.c \
	eventProcessing.c $(HEADERS) -o $(BIN_PATH)/$@

stringProcessingTestApp2:
	$(CC) $(CFLAGS) test_apps/stringProcessingTestApp2.c eventList.c stringProcessing.c \
	eventProcessing.c $(HEADERS) -o $(BIN_PATH)/$@

clean:
	rm -rf $(TARGETS) $(BIN_PATH) *.o *.gch

create_bin:
	mkdir $(BIN_PATH)

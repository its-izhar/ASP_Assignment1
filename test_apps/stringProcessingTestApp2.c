#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "calenderFilter.h"


#define MAX 5

event_t eventA[MAX] = {
  {'C', "Meeting1  ", "NEB201    ", "11/02/2017", "01:30"},
  {'C', "Meeting2  ", "NEB202    ", "12/02/2017", "02:30"},
  {'C', "Meeting3  ", "NEB203    ", "13/02/2017", "03:30"},
  {'C', "Meeting4  ", "NEB204    ", "14/02/2017", "04:30"},
  {'C', "Meeting5  ", "NEB205    ", "15/02/2017", "05:30"}
};


int main(int argc, char const *argv[])
{
  char buffer[BUFFERSIZE] = {};       // Buffer to hold a line of the string
  event_t newEvent;                   // Event to hold new event entry
  int totalStringsCount = 0;

  memset(buffer, 0, BUFFERSIZE);      // Reset the buffer
  // Read a line from stdin and process it
  while(fgets(buffer, BUFFERSIZE , stdin) > 0)
  {
    buffer[BUFFERSIZE-1] = '\0';          // Force the end of the string
    dbg_trace("APP: String [size: %d]: %s", (int) strlen(buffer), buffer);
    // We assume that the given string is valid, so we parse
    parseEvent(buffer, &newEvent);

    if(totalStringsCount < MAX){
      dbg_info("before: \n");
      displayEvent(&eventA[totalStringsCount]);
      updateEvent(&eventA[totalStringsCount], &newEvent);
      dbg_info("after: \n");
      displayEvent(&eventA[totalStringsCount]);
    }

    ++totalStringsCount;
    // Clear the buffer before reading next string
    memset(&newEvent, 0, sizeof(event_t));
    memset(buffer, 0, BUFFERSIZE);
    dbg_info("\n");
  }

  return 0;
}

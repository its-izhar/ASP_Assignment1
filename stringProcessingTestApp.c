#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "calenderFilter.h"


/* Buffersize to hold a line of the string */
#define BUFFERSIZE 50
char buffer[BUFFERSIZE] = {};


int main(int argc, char const *argv[])
{
  int totalStringsCount = 0;
  event_t nEvent;
  node_t *list = NULL;

  // Read a line from stdin and process it
  while(fgets(buffer, BUFFERSIZE , stdin) > 0)
  {
    // Force the end of the string
    buffer[BUFFERSIZE-1] = '\0';
    // Keep the count of the total strings read from stdin
    ++totalStringsCount;
    //dbg_trace("String [size: %d]: %s\n", (int) strlen(buffer), buffer);
    //print_output("%s", buffer);

    // We assume that the given string is valid, so we parse
    parseEvent(buffer, &nEvent);
    insertNode(&list, totalStringsCount, &nEvent);
    // Clear the buffer before reading next string
    memset(buffer, 0, BUFFERSIZE);
  }
  displayList(list);
  print_output("List length: %d, Expected: %d\n", listLength(list), totalStringsCount);

  // Check the getNode logic
  for(int i=1; i<listLength(list); i++)
  {
    if(SUCCESS == getNode(list, i, &nEvent)){
      print_output("Index: %d, Event: %s,%s,%s,%s\n",
          i, nEvent.title, nEvent.date, nEvent.time, nEvent.location);
    }
    else {
      print_output("Failed at index: %d\n", i);
    }
  }

  // Checking the events logic here
  int LLength = listLength(list);
  event_t iteratorEvent;

  for(int position=1; position <= LLength; position++)
  {
    getNode(list, position, &nEvent);
    print_output("Index: %d, Event: %s,%s,%s,%s\n",
        position, nEvent.title, nEvent.date, nEvent.time, nEvent.location);
    print_output("%s","\t Duplicates found at indexes: \n");

    for(int iterator=1; iterator <= LLength; iterator++)
    {
      getNode(list, iterator, &iteratorEvent);
      if(position != iterator)
      {
        if(1 == isSameEvent(&nEvent, &iteratorEvent))
        {
          print_output("\t\t %d: %s,%s,%s,%s \n", iterator,
            iteratorEvent.title, iteratorEvent.date, iteratorEvent.time, iteratorEvent.location);
        }
      }
    }
    print_output("%s","\n\n");
  }

  // delete the list (to free the space allocated)
  deleteList(&list);

  return 0;
}

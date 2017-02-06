#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "calenderFilter.h"


/* Buffersize to hold a line of the string */
char buffer[BUFFERSIZE] = {};


int main(int argc, char const *argv[])
{
  int totalStringsCount = 0;
  event_t nEvent;
  node_t *list = NULL;
  node_t *sortedList = NULL;

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
    dbg_trace("Index: %d, Event: %s,%s,%s,%s\n",
        sortedInsert(&sortedList, &nEvent), nEvent.title, nEvent.date, nEvent.time, nEvent.location);
    // Clear the buffer before reading next string
    memset(buffer, 0, BUFFERSIZE);
  }
  displayList(list);
  print_output("List length: %d, Expected: %d\n", listLength(list), totalStringsCount);
  displayList(sortedList);
  print_output("List length: %d, Expected: %d\n", listLength(sortedList), totalStringsCount);

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

  // Checking the same events logic here
  int LLength = listLength(list);
  event_t iteratorEvent;

  for(int position=1; position <= LLength; position++)
  {
    getNode(list, position, &nEvent);
    print_output("Index: %d, Event: %s,%s,%s,%s\n",
        position, nEvent.title, nEvent.date, nEvent.time, nEvent.location);
    print_output("%s","\t Duplicates found at indexes: \n");
    isEventPresentInTheList(list, &nEvent, NULL);
    print_output("%s","\n\n");
  }

  // Tests for checking if event1 is earlier than event2
  getNode(list, 1, &nEvent);
  getNode(list, 3, &iteratorEvent);

  if(true == isEarlierInTime(&nEvent, &iteratorEvent))
    dbg_trace("%s is earlier than %s\n", nEvent.time, iteratorEvent.time);
  else
    dbg_trace("%s is earlier than %s\n", iteratorEvent.time, nEvent.time);


  // Checking for earlierInTime Events here
  for(int position=1; position <= LLength; position++)
  {
    getNode(list, position, &nEvent);
    print_output("Index: %d, Event: %s,%s,%s,%s\n",
        position, nEvent.title, nEvent.date, nEvent.time, nEvent.location);
    print_output("%s","\t Earlier in Time Events found at indexes: \n");

    for(int iterator=1; iterator <= LLength; iterator++)
    {
      getNode(list, iterator, &iteratorEvent);
      if(position != iterator)
      {
        if(true == isEarlierInTime(&iteratorEvent, &nEvent))
        {
          print_output("\t\t %d: %s,%s,%s,%s \n", iterator,
            iteratorEvent.title, iteratorEvent.date, iteratorEvent.time, iteratorEvent.location);
        }
      }
    }
    print_output("%s","\n\n");
  }

  // get the earlist event of the day
  getEarliestEventOfTheDay(sortedList, &nEvent);
  print_output("Earliest Event: %s,%s,%s,%s\n",
      nEvent.title, nEvent.date, nEvent.time, nEvent.location);

  // delete the list (to free the space allocated)
  deleteList(&list);
  deleteList(&sortedList);

  return 0;
}

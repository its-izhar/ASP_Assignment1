#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "debugMacros.h"
#include "calenderFilter.h"



/* Process the new event create request */
static void processEventCreate(stringPool_t **pool, event_t *event)
{
  stringPool_t *poolHandle = *pool;
  int dateIndex = -1;
  event_t earliestEvent;

  // Check if the date is present in the date pool, if not, add to pool
  bool status = getEventDateIndexFromPool(poolHandle, event->date, &dateIndex);
  if((status == FAIL) || (dateIndex == -1))
  {
    dbg_trace("APP: %s is not present in the pool!\n", event->date);
    dbg_trace("APP: Adding %s to the pool now.\n", event->date);
    // it's not present, so add to the pool
    bool addStatus = addEventDateToPool(&poolHandle, event->date);
    if(addStatus == SUCCESS){
      dbg_trace("APP: Successfully added %s to the date pool at index %d.\n",
                            event->date, poolHandle->count - 1);
    }
    dateIndex = poolHandle->count - 1;
  }

  // Check if the new event is already present
  if(dateIndex > -1)
  {
    dbg_trace("APP: List Head at : %p\n", poolHandle->eventList[dateIndex]);
    bool isPresent = isEventPresentInTheList(poolHandle->eventList[dateIndex], event, NULL);
    // If it is already in the list, we know this one's a duplicate, so return
    if(isPresent == true){
      dbg_info("APP: New event is already present in the list. returning.\n");
      goto RETURN;
    }
    else {
      // since it is not present, we add it to the list
      int eventPositionInList = sortedInsert(&poolHandle->eventList[dateIndex], event);
      dbg_trace("APP: Added the event at position %d, List head at: %p\n",
                eventPositionInList, poolHandle->eventList[dateIndex]);
    }
    // Once the event is added to the list, check if it is the earliest on that day
    getEarliestEventOfTheDay(poolHandle->eventList[dateIndex], &earliestEvent);
    if(true == isSameEvent(event, &earliestEvent)){
      dbg_info("APP: Requested event is the earliest event!\n");
      goto PRINT_OUTPUT;
    }
    else {
      goto RETURN;
    }
  }

PRINT_OUTPUT:
  print_output("%s:%s\n", event->date, event->location);

RETURN:
  // Update the poolHandle in the caller before going back
  *pool = poolHandle;
}


/* Process the new event delete request */
static void processEventDelete(stringPool_t **pool, event_t *event)
{
  stringPool_t *poolHandle = *pool;
  int dateIndex = -1;
  int eventIndex = -1;
  event_t earliestEvent;

  // Check if the date is present in the date pool, if not, return
  bool status = getEventDateIndexFromPool(poolHandle, event->date, &dateIndex);
  if((status == FAIL) || (dateIndex == -1))
  {
    dbg_trace("APP: %s is not present in the pool! Returning!\n", event->date);
    goto RETURN;
  }
  dbg_trace("APP: List Head at : %p\n", poolHandle->eventList[dateIndex]);
  displayList(poolHandle->eventList[dateIndex]);
  //dbg_trace("Found Index: %d\n", dateIndex);

  // If we have the index, that means the date entry is present in the pool
  if(dateIndex > -1)
  {
    bool isPresent = isEventPresentInTheList(poolHandle->eventList[dateIndex], event, &eventIndex);
    dbg_trace("eventIndex: %d\n", eventIndex);
    // If it is present in the list, we will delete it
    if(isPresent == true)
    {
      dbg_trace("APP: Requested event to be deleted is found at %d position in the list.\n", eventIndex);
      // Before deleting, check if the event to be deleted is the earliestEvent for the day
      getEarliestEventOfTheDay(poolHandle->eventList[dateIndex], &earliestEvent);
      if(true == isSameEvent(event, &earliestEvent))
      {
        dbg_info("APP: Requested event to be deleted is the earliest event!\n");
        // Print to output (Location: None)
        print_output("%s:%s\n", event->date, "None");
      }
      // Delete the node from the list
      deleteNode(&poolHandle->eventList[dateIndex], eventIndex);
    }
    else {
      // since it is not present, we just return
      dbg_info("Requested event to be deleted is not found! Returning!\n");
    }
  }

RETURN:
  // Update the poolHandle in the caller before going back
  *pool = poolHandle;
}



/************************ Main() *******************************/
int main(int argc, char const *argv[])
{
  char buffer[BUFFERSIZE] = {};       // Buffer to hold a line of the string
  event_t newEvent;                   // Event to hold new event entry
  stringPool_t *eventPool = NULL;     // Event Pool according to dates
  int totalStringsCount = 0;

  // create the string pool
  eventPool = createStringPool(POOL_CAPACITY);

  memset(buffer, 0, BUFFERSIZE);      // Reset the buffer
  // Read a line from stdin and process it
  while(fgets(buffer, BUFFERSIZE , stdin) > 0)
  {
    buffer[BUFFERSIZE-1] = '\0';          // Force the end of the string

    // Pad the unnecessary buffer with null-termination
    int bufferIndex = BUFFERSIZE - 1;
    while(!isalnum(buffer[bufferIndex])){
      buffer[bufferIndex] = '\0';
      --bufferIndex;
    }
    ++totalStringsCount;
    dbg_trace("APP: String [size: %d]: %s\n", (int) strlen(buffer), buffer);
    // We assume that the given string is valid, so we parse
    parseEvent(buffer, &newEvent);

    // Process Events
    switch(newEvent.mode)
    {
      case EVENT_CREATE:
        processEventCreate(&eventPool, &newEvent);
        break;

      case EVENT_DELETE:
        processEventDelete(&eventPool, &newEvent);
        break;

      case EVENT_MODIFY:
        break;

      default:
        dbg_info("APP: Unknown Mode! Error!");
    }

    // Clear the buffer before reading next string
    memset(&newEvent, 0, sizeof(event_t));
    memset(buffer, 0, BUFFERSIZE);
    dbg_info("\n");
  }
  // Printing the count of total strings and the valid strings
  dbg_trace("APP: Total Strings: %d\n\n", totalStringsCount);

  // Display the contents of the string pool
  displayEventDatePool(eventPool);

  // destroy the pool
  destroyEventDatePool(&eventPool);

  return 0;
}

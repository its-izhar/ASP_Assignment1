#include "calenderFilter.h"

#define MAX_STR 10

const char *dateString[MAX_STR] = {
  "11/01/2017",
  "12/01/2017",
  "13/01/2017",
  "14/01/2017",
  "15/01/2017",
  "16/01/2017",
  "17/01/2017",
  "18/01/2017",
  "19/01/2017",
  "20/01/2017"
};

int main(int argc, char *argv[])
{
  int poolCapacity = 30;
  char date[11];

  stringPool_t *datePool = createStringPool(poolCapacity);
  if(datePool == NULL){
    print_output("%s", "Memory Error!\n");
    return 0;
  }

  // Sample event
  event_t newEvent = {'C', "Meeting   ", "NEB202    ", "01/20/2017", "03:45" };

  int getIndex = -1;
  // Just to check
  displayEventDatePool(datePool);

  for(int i=0; i<MAX_STR; i++)
  {
    snprintf(date, DATE_STRING_MAX_SIZE, "%s", dateString[i]);
    addEventDateToPool(&datePool, date);
    int status = getEventDateIndexFromPool(datePool, date, &getIndex);
    if(status == SUCCESS && getIndex != -1){
      dbg_trace("Creating new list at index: %d for %s\n", getIndex, date);
      sortedInsert(&datePool->eventList[getIndex], &newEvent);
    }
    displayEventDatePool(datePool);
  }

  displayEventDatePool(datePool);

  // See if the event date is present in the pool
  for(int i=0; i<MAX_STR; i++)
  {
    int status = getEventDateIndexFromPool(datePool, (char*)dateString[MAX_STR-1-i], &getIndex);
    if(status == FAIL || getIndex == -1){
      dbg_trace("Failed to find %s in the pool!\n", dateString[MAX_STR-1-i]);
    }
    else{
      dbg_trace("Found %s at %d in the pool!\n", dateString[MAX_STR-1-i], getIndex);
    }
  }

  // Destroy the pool to free up the space
  destroyEventDatePool(&datePool);

  return 0;
}

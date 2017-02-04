#include <stdlib.h>
#include <stdbool.h>
#include "calenderFilter.h"



/* returns true if the srcEvent is earlier in time than destEvent */
int isEarlierInTime(event_t *srcEvent, event_t *destEvent)
{
  int srcEventHH=0, srcEventMM=0, destEventHH=0, destEventMM=0;
  bool isEarlierInTime = false;
  char *srcPtr=NULL, *destPtr=NULL;

  if ((srcEvent == NULL) || (destEvent == NULL)){
    dbg_info("Invalid Event Pointers!\n");
    return isEarlierInTime;
  }
  // srcPtr and destPtr will have addressess of ':' characters from the date string
  // after the first two calls to strtol
  srcEventHH = (int) strtol(srcEvent->time, &srcPtr, 10);
  destEventHH = (int) strtol(destEvent->time, &destPtr, 10);
  ++srcPtr;
  ++destPtr;
  srcEventMM = (int) strtol(srcPtr, NULL, 10);
  destEventMM = (int) strtol(destPtr, NULL, 10);

#if 0
  dbg_trace("srcEvent->time: %s, destEvent->time: %s\n",
                  srcEvent->time, destEvent->time);
  dbg_trace("srcEvent-HH:MM: %d:%d, destEvent-HH:MM: %d:%d\n",
                  srcEventHH, srcEventMM, destEventHH, destEventMM);
#endif

  if(srcEventHH < destEventHH){
    isEarlierInTime = true;
  }
  else if(srcEventHH == destEventHH) {
    if(srcEventMM < destEventMM){
      isEarlierInTime = true;
    }
  }
  return isEarlierInTime;
}


/* returns the earliest event of a perticular day */
int getEarliestEventOfTheDay(node_t *sortedEventList, event_t *OutEvent)
{
  if(sortedEventList == NULL){
    return FAIL;
  }
  // since we know that the event list is already sorted, the earliest event of
  // a perticular day will be at it's head position, i.e. position 1,
  // so we simply return that
  return getNode(sortedEventList, 1, OutEvent);
}

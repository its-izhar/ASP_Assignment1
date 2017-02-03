#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "calenderFilter.h"


// Parse the given the string from the buffer to event_t data struct
void parseEvent(char *buffer, event_t *event)
{
  char eventString[50];
  const char delimiter[2] = ",";
  char *token;
  int pass = 0;

  // Make a copy of the original buffer as strtok will modify it otherwise
  strcpy(eventString, buffer);
  memset(event, 0, sizeof(event_t));

  /* get the first token (which is mode in our case) */
  token = strtok(eventString, delimiter);
  event->mode = token[0];

  /* walk through other tokens */
  while( token != NULL )
  {
    ++pass;
    token = strtok(NULL, delimiter);

    if(pass == 1) {
      strcpy(event->title, token);
      event->title[TITLE_STRING_SIZE] = '\0';
    }
    else if(pass == 2) {
      strcpy(event->date, token);
      event->date[DATE_STRING_SIZE] = '\0';
    }
    else if(pass == 3) {
      strcpy(event->time, token);
      event->time[TIME_STRING_SIZE] = '\0';
    }
    else if(pass == 4) {
      strcpy(event->location, token);
      event->location[LOCATION_STRING_SIZE] = '\0';
    }
  }
}

/* returns true if size bytes of str1 are equal to str2 */
int isSameString(char *str1, char *str2, int size)
{
  return !strncmp(str1, str2, size);
}

/* returns true if the two requested events are same */
int isSameEvent(event_t *event1, event_t *event2)
{
  bool isSame = false;

  if ((event1 == NULL) || (event2 == NULL)){
    dbg_info("Invalid Event Pointers!\n");
    isSame = false;
    return isSame;
  }

  if(isSameString(event1->title, event2->title, TITLE_STRING_SIZE)
      && isSameString(event1->date, event2->date, DATE_STRING_SIZE)
      && isSameString(event1->time, event2->time, TIME_STRING_SIZE)
      && isSameString(event1->location, event2->location, LOCATION_STRING_SIZE))
      {
        //dbg_info("event1 and event2 are same!\n");
        isSame = true;
      }

  return isSame;
}

#if 0
/* returns true if the srcEvent is earlier in time than destEvent */
int isEarlierInTime(event_t *srcEvent, event_t *destEvent)
{
  int srcEventHH=0, srcEventMM=0, destEventHH=0, destEventMM=0;
  //bool isEarlierInTime = false;
  char *srcPtr=NULL, *destPtr=NULL;

  srcEventHH = (int) strtol(srcEvent->time, &srcPtr, 10);
  destEventHH = (int) strtol(destEvent->time, &destPtr, 10);
  ++srcPtr;
  ++destPtr;
  srcEventMM = (int) strtol(srcPtr, NULL, 10);
  destEventMM = (int) strtol(destPtr, NULL, 10);

  dbg_trace("srcEvent->time: %s, destEvent->time: %s\n",
                  srcEvent->time, destEvent->time);
  dbg_trace("srcEvent-HH:MM: %d:%d, destEvent-HH:MM: %d:%d\n",
                  srcEventHH, srcEventMM, destEventHH, destEventMM);

  return true;
}
#endif

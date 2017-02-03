#include <string.h>
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

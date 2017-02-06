#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "calenderFilter.h"

#define MAX 2

event_t event[MAX] = {
  {'C', "Info      ", "NEB555    ", "01/13/2017", "07:30"},
  {'C', "Meeting2  ", "NEB202    ", "01/13/2017", "18:30"}
};

int main(int argc, char const *argv[])
{
  char buffer[BUFFERSIZE] = {0};
  int totalStringsCount = 0;
  event_t nEvent;
  node_t *list = NULL;

  // Read a line from stdin and process it
  while(fgets(buffer, BUFFERSIZE , stdin) > 0)
  {
    // Force the end of the string
    buffer[BUFFERSIZE-1] = '\0';
    // Pad the unnecessary buffer with null-termination
    int bufferIndex = BUFFERSIZE - 1;
    while(!isalnum(buffer[bufferIndex])){
      buffer[bufferIndex] = '\0';
      --bufferIndex;
    }
    ++totalStringsCount;
    dbg_trace("String [size: %d]: %s\n", (int) strlen(buffer), buffer);

    // We assume that the given string is valid, so we parse
    parseEvent(buffer, &nEvent);
    sortedInsert(&list, &nEvent);

    // Clear the buffer before reading next string
    memset(&nEvent, 0, sizeof(event_t));
    memset(buffer, 0, BUFFERSIZE);
  }
  displayList(list);
  print_output("List length: %d, Expected: %d\n", listLength(list), totalStringsCount);

  int eventIndex = -1;
  event_t eventToModify;
  for(int i = 0; i < MAX; i++)
  {
    bool status = getEventIDWithMatchingTitleFromList(list, &event[i], &eventIndex);
    if((status != FAIL) || (eventIndex != -1))
    {
      getNode(list, eventIndex, &eventToModify);
      setNode(list, eventIndex, &event[i]);
    }
    displayList(list);
    print_output("List length: %d, Expected: %d\n\n", listLength(list), totalStringsCount);

    // sort the list now
    sortEventList(&list);
    displayList(list);
    print_output("List length: %d, Expected: %d\n", listLength(list), totalStringsCount);
  }
  // delete the list (to free the space allocated)
  deleteList(&list);

  return 0;
}

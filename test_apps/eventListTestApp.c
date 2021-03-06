#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "calenderFilter.h"


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
    insertNode(&list, totalStringsCount, &nEvent);

    // Clear the buffer before reading next string
    memset(&nEvent, 0, sizeof(event_t));
    memset(buffer, 0, BUFFERSIZE);
  }
  displayList(list);
  print_output("List length: %d, Expected: %d\n", listLength(list), totalStringsCount);

  // Random deletions
  print_output("%s","\nRandom test of deletions ...\n\n");

  for(int times=1; times<=5; times++)
  {
    int r_pos = rand() % (listLength(list)+1);   // Random positions

    if(r_pos > 0){
      --totalStringsCount;
    }
    deleteNode(&list, r_pos);
    displayList(list);
  }
  print_output("List length: %d, Expected: %d\n\n\n", listLength(list),
      (totalStringsCount < 0)? 0 : totalStringsCount );

  // deleting continuously from both the ends
  for(int times=1; times<=6; times++)
  {
    if(times <= 3){
      deleteNode(&list, listLength(list));
      --totalStringsCount;
    }
    else{
      deleteNode(&list, 1);
      --totalStringsCount;
    }
    displayList(list);
  }
  print_output("List length: %d, Expected: %d\n\n\n", listLength(list),
    (totalStringsCount < 0)? 0 : totalStringsCount );

  // delete the list (to free the space allocated)
  deleteList(&list);

  return 0;
}

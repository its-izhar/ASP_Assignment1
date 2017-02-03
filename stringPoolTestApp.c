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
  int poolCapacity = 2;
  char date[10];

  stringPool_t *datePool = createStringPool(poolCapacity);
  if(datePool == NULL){
    print_output("%s", "Memory Error!\n");
    return 0;
  }

  // Just to check
  displayEventDatePool(datePool);

  for(int i=0; i<MAX_STR; i++)
  {
    snprintf(date, 10, "%s", dateString[i]);
    addEventDateToPool(&datePool, date);
    displayEventDatePool(datePool);
  }

  // Destroy the pool to free up the space
  destroyEventDatePool(datePool);

  return 0;
}

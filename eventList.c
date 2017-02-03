#include <stdlib.h>
#include <string.h>
#include "calenderFilter.h"
#include "debugMacros.h"



/* returns the list of the length */
int listLength(node_t *head)
{
  node_t *current = head;
  int count = 0;

  while(current != NULL)
  {
    ++count;
    current = current->next;
  }
  return count;
}



/* displays the contents of the list */
void displayList(node_t *head)
{
  node_t *current = head;

  print_output("%s\n", "***List contents:");
  while(current != NULL)
  {
    print_output("Mode: %c, Title: %s, Date: %s, Time: %s, Location: %s\n",
      current->event.mode, current->event.title, current->event.date,
      current->event.time, current->event.location);

    current = current->next;
  }
  print_output("%s\n","***End!");
}



/* insert elements in the list */
int insertNode(node_t **head, int position, event_t *event)
{
  node_t *newNode, *previousNode, *positionNode;
  int count=1;

  // get the current head of the list
  positionNode = *head;

  // Error checking
  if(position < 1){
    dbg_trace("Invalid position: %d. Must be greater than or equal to 1.\n", position);
    return FAIL;
  }

  // Get the new node and store the data in it
  newNode = (node_t *) calloc(1, sizeof(node_t));
  if(newNode == NULL){
    dbg_info("Can't allocate memory for new node! Exiting!\n");
    return FAIL;
  }
  memcpy(&newNode->event, event, sizeof(event_t));
  newNode->next = NULL;

  // Inserting at the beginning of the list
  if(position == 1)
  {
    newNode->next = positionNode;         // newNode points to positionNode now
    *head = newNode;                      // New node is head now
  }
  else
  {
    // Traverse until we find the desired position of the node or reach the end,
    // insert the node at the position of whichever earliest
    while((positionNode != NULL) && (count < position))
    {
      count++;
      previousNode = positionNode;
      positionNode = positionNode->next;
    }
    previousNode->next = newNode;
    newNode->next = positionNode;
  }
  dbg_trace("inserted '%s:%s' at position %d in '%s' list.\n",
    newNode->event.title, newNode->event.time, position, newNode->event.date);

  return SUCCESS;
}



/* deletes elements from the list */
int deleteNode(node_t **head, int position)
{
  node_t *previousNode, *positionNode;
  int count=1;

  // get the current head of the list
  positionNode = *head;

  // Error checking
  if(positionNode == NULL){
    dbg_info("List is already empty!\n");
    return FAIL;
  }
  if(position < 1){
    dbg_trace("Invalid position: %d. Must be greater than or equal to 1.\n", position);
    return FAIL;
  }

  // Deleting the node from the beginning of the list
  if(position == 1)
  {
    *head = positionNode->next;         // Update the head to next node
    dbg_trace("deleted '%s:%s' at position %d in '%s' list.\n",
      positionNode->event.title, positionNode->event.time, position, positionNode->event.date);
    free(positionNode);
    positionNode->next = NULL;          // Remove the first node
  }
  else
  {
    // Traverse until we find the desired position of the node or reach the end,
    // delete the node at the position of whichever earliest
    while((positionNode != NULL) && (count < position))
    {
      count++;
      previousNode = positionNode;
      positionNode = positionNode->next;
    }
    if(positionNode == NULL)
    {
      dbg_info("Reached the end of the list. No node to delete! Returning.\n");
      return FAIL;
    }
    previousNode->next = positionNode->next;
    dbg_trace("deleted '%s:%s' at position %d in '%s' list.\n",
      positionNode->event.title, positionNode->event.time, position, positionNode->event.date);
    free(positionNode);
    positionNode->next = NULL;
  }
  return SUCCESS;
}



/* Deletes the entire linked list */
void deleteList(node_t **head)
{
  node_t *auxNode, *current;

  // make the current one point to the head
  current = *head;
  while(current != NULL)
  {
    auxNode = current->next;
    free(current);
    current = auxNode;
  }
  // Make the change visible to the caller
  *head = NULL;
}

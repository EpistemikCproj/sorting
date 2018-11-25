/* queueADT.h - implements the queue ADT */#ifndef MHS_QUEUEADT_H#define MHS_QUEUEADT_H
#include <stdio.h>#include <stdlib.h>typedef int element ;typedef enum boolean { False, True } BOOLEAN ;typedef struct _queuenode {	  element contents ;	  struct _queuenode* next ;	  } QueueNode ;typedef QueueNode* NodePointer ;typedef struct _queue {	  NodePointer first, last ;	  } Queue ;typedef Queue* Qptr ;/************** FUNCTION  PROTOTYPES ****************/void GetNode(NodePointer*);void ReturnNode(NodePointer*);void CreateQ(Qptr);BOOLEAN IsEmpty(Qptr);void Enq(Queue*, element);element Deq(Queue *);void PrintQ(Queue *) ;BOOLEAN MemCheck();#endif // MHS_QUEUEADT_H
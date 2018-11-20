// Linked list of transport card records implementation ... Assignment 1 COMP9024 18s2
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cardLL.h"
#include "cardRecord.h"

// linked list node type
// DO NOT CHANGE
typedef struct node {
    cardRecordT data;
    struct node *next;
} NodeT;

// linked list type
typedef struct ListRep {
   NodeT *head;

/* Add more fields if you wish */

} ListRep;

/*** Your code for stages 2 & 3 starts here ***/

// Time complexity: O(1)
// Explanation: There is no iterative in this function, so the complexity is constant.
List newLL() {
	List list;
	list = (List)malloc(sizeof(ListRep));
	list->head=NULL;
	return list;      /* needs to be replaced */
}

// Time complexity: O(n)
// Explanation: The function only needs to iterate among the linkedlist, to check whether
//              a cardID has been added and compare the new node's balance with each node's
//              balance.
void insertLL(List listp, int cardID, float amount) {
   NodeT *p;
   p = listp->head;
   cardRecordT cardRecord;
   cardRecord.cardID = cardID;
   cardRecord.balance = amount;
   while (p != NULL) {
      if ((p->data).cardID == cardID) {
         cardRecord.balance = (p->data).balance + amount;
         p->data = cardRecord;
         printCardData(cardRecord);
         return;
      }
      p = p->next;
   }

   NodeT *new;
   new = (NodeT *)malloc(sizeof(NodeT));
   assert(new != NULL);
   new->data = cardRecord;

   p = listp->head;
   if (p == NULL) {
      listp->head = new;
      new->next = NULL;
      printf("Card added.\n");
      return;
   }
   if ((listp->head->data).cardID > (new->data).cardID) {
      new->next = listp->head;
      listp->head = new;
      printf("Card added.\n");
      return;
   } else {
      while (p->next!=NULL) {
         if ((p->next->data).cardID > (new->data).cardID) {
            new->next = p->next;
            p->next = new;
            printf("Card added.\n");
            return;
         }
         p = p->next;
      }
      p->next = new;
      new->next = NULL;
      printf("Card added.\n");
      return;
   }             /* needs to be replaced */
}

// Time complexity: O(n)
// Explanation: This function free each nodes after change the head of linkedlist to its next node.
//              the pointer *p only iterate from head to tail. So the complexity is linear.
void dropLL(List listp) {
   NodeT *p;
   p = listp->head;
   while (p!= NULL) {
      listp->head = p->next;
      free(p);
      p = listp->head;
   }
   return;  /* needs to be replaced */
}

// Time complexity: O(n)
// Explanation: This function makes the pointer p iterate from head to tail in order to find the 
//              node that want to be deleted. So the complexity is linear.
void removeLL(List listp, int cardID) {
   NodeT *p;
   int flag = 0;
   p = listp->head;
   if ((p->data).cardID == cardID) {
      listp->head = p->next;
      printf("Card removed.\n");
      return;
   } else {
      while (p->next!=NULL) {
         if ((p->next->data).cardID == cardID) {
            p->next = p->next->next;
            flag = 1;
            printf("Card removed.\n");
            break;
         }
         p = p->next;
      }
   }
   if (flag == 0) {
      printf("Card not found.\n");
   }
   return;  /* needs to be replaced */
}

// Time complexity: O(n)
// Explanation: This function makes the pointer iterate from head to tail to count the number of 
//              nodes and total balance. So the complexity is linear. I will caculate the average
//              balance in the main function.
void getAverageLL(List listp, int *n, float *balance) {
   *n = 0;
   *balance = 0;
   NodeT *p;
   p = listp->head;
   while (p!=NULL) {
      (*n) += 1;
      (*balance) += (p->data).balance;
      p = p->next;
   }
   return;  /* needs to be replaced */
}

// Time complexity: O(n)
// Explanation: This function makes the pointer iterate from head to tail for printing out the record.
//              So the complexity is linear.
void showLL(List listp) {
   NodeT *p;
   p = listp->head;
   while (p != NULL) {
      printCardData(p->data);
      p = p->next;
   }
   return;  /* needs to be replaced */
}



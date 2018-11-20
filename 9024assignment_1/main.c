/**
     main.c

     Program supplied as a starting point for
     Assignment 1: Transport card manager

     COMP9024 18s2
**/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "cardRecord.h"
#include "cardLL.h"

void printHelp();
void CardLinkedListProcessing();

int main(int argc, char *argv[]) {
   if (argc == 2) {

      /*** Insert your code for stage 1 here ***/
      int num_of_elements = atoi(argv[1]);
      cardRecordT *arr = malloc(num_of_elements * sizeof(cardRecordT));
      assert(arr != NULL);
      
      // input cardID, amount to each element.
      int i;
      for (i=0;i<num_of_elements;i++) {
          arr[i].cardID = readValidID();
          arr[i].balance = readValidAmount();
      }
      
      // print elements and sum up all amount value, then caculate the average.
      float sum = 0.0;
      for (i=0;i<num_of_elements;i++) {
          sum += arr[i].balance;
          printCardData(arr[i]);
      }
      
      printf("Number of cards on file: %d\n", num_of_elements);
      if (sum >= 0) {
         if (num_of_elements==0) {
            printf("Average balance: $%.2lf\n",0.0);
         } else {
            printf("Average balance: $%.2lf\n", sum/num_of_elements);
         }
      } else{
         printf("Average balance: -$%.2lf\n", -sum/num_of_elements);
      }
      free(arr);
   } else {
      CardLinkedListProcessing();
   }
   return 0;
}

/* Code for Stages 2 and 3 starts here */

void CardLinkedListProcessing() {
   int op, ch;

   List list = newLL();   // create a new linked list
   
   while (1) {
      printf("Enter command (a,g,p,q,r, h for Help)> ");

      do {
	  ch = getchar();
      } while (!isalpha(ch) && ch != '\n');  // isalpha() defined in ctype.h
      op = ch;
      // skip the rest of the line until newline is encountered
      while (ch != '\n') {
	  ch = getchar();
      }

      switch (op) {
         case 'a':
         case 'A':
            /*** Insert your code for adding a card record ***/
         {
            int cardID = readValidID();
            float amount = readValidAmount();
            insertLL(list, cardID, amount);
            break;
         }

         case 'g':
         case 'G':
            /*** Insert your code for getting average balance ***/
         {
            int *n = (int *)malloc(sizeof(int));
            float *balance1 = (float *)malloc(sizeof(float));
            getAverageLL(list, n, balance1);
            printf("Number of cards on file: %d\n", *n);
            if (*balance1 >= 0) {
               if (*n != 0) {
                  printf("Average balance: $%.2lf\n", (*balance1)/(*n));
               } else {
                  printf("Average balance: $%.2lf\n", 0.0);
               }
            } else {
               printf("Average balance: -$%.2lf\n", -(*balance1)/(*n));
            }
	        break;
         }
	    
         case 'h':
         case 'H':
            printHelp();
	        break;
	    
         case 'p':
         case 'P':
            /*** Insert your code for printing all card records ***/
            showLL(list);
            break;

         case 'r':
         case 'R':
            /*** Insert your code for removing a card record ***/
         {
            int cardID = readValidID();
            removeLL(list, cardID);
	        break;
         }

	     case 'q':
         case 'Q':
            dropLL(list);       // destroy linked list before returning
	    printf("Bye.\n");
	    return;
      }
   }
}

void printHelp() {
   printf("\n");
   printf(" a - Add card record\n" );
   printf(" g - Get average balance\n" );
   printf(" h - Help\n");
   printf(" p - Print all records\n" );
   printf(" r - Remove card\n");
   printf(" q - Quit\n");
   printf("\n");
}

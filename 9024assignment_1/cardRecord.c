// Transport card record implementation ... Assignment 1 COMP9024 18s2
#include <stdio.h>
#include "cardRecord.h"

#define LINE_LENGTH 1024
#define NO_NUMBER -999

// scan input line for a positive integer, ignores the rest, returns NO_NUMBER if none
int readInt(void) {
   char line[LINE_LENGTH];
   int  n;

   fgets(line, LINE_LENGTH, stdin);
   if ( (sscanf(line, "%d", &n) != 1) || n <= 0 )
      return NO_NUMBER;
   else
      return n;
}

// scan input for a floating point number, ignores the rest, returns NO_NUMBER if none
float readFloat(void) {
   char  line[LINE_LENGTH];
   float f;

   fgets(line, LINE_LENGTH, stdin);
   if (sscanf(line, "%f", &f) != 1)
      return NO_NUMBER;
   else
      return f;
}

int readValidID(void) {
   int a;
   printf("Enter card ID: ");
   a = readInt();
   while (a<10000000 || a>99999999) {
      printf("Not valid. Enter a valid value: ");  
      a = readInt();   
   };
   return a;
     /* needs to be replaced */
}

float readValidAmount(void) {
   float a;
   printf("Enter amount: ");
   a = readFloat();
   while (a<-2.35||a>250) {
      printf("Not valid. Enter a valid value: ");
      a = readFloat();
   };
   return a;  /* needs to be replaced */
}

void printCardData(cardRecordT card) {
   printf("-----------------\n");
   printf("Card ID: %d\n", card.cardID);
   if (card.balance >= 0) {
      printf("Balance: $%.2lf\n", card.balance);
   } else {
      printf("Balance: -$%.2lf\n", -card.balance);
   }
   if (card.balance < 5.0) {
      printf("Low balance\n");
   };
   printf("-----------------\n");
   return;  /* needs to be replaced */
}


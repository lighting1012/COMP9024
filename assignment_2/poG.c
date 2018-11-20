/**
   poG.c

   COMP9024 18s2 Assignment 2: Partial Order Graphs
   coded by Jiaquan Xu
   2018-10-4
   
**/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

// include Graph adt
#include "Graph.c"

// function declaration
int contained_number(int,int);
int longer(int A[1000], int B[1000]);
int max(int A,int B);
int depth_recursive(int i, Graph g);
void print_route(int i,Graph g,int *arr,int history[]);

int dp[1000];

int main(int argc, char *argv[]) {
   if (argc != 2) {
      return 0;
   } else {

      int original_number = atoi(argv[1]);
      int i,k,m;
      int number=0;
      int arr[1000];
      Edge e;

      // Find divisor
      // if there is an argument, then find all of its divisors and store it in an array
      for (i=1;i<=(original_number/2);i++) {
         if (original_number%i==0) {
            arr[number] = i;
            number++;
         } 
      }
      arr[number] = original_number;

      // -- task A --
      // TIME COMPLEXITY: O(n*n*m*m), which n is number of divisors, m is lenth of decimal p.

      // Graph initialization
      // for all the divisors, if it is contained and divided by another number
      // insert edge to them
      Graph g = newGraph(number+1); 
      for (i=0;i<number;i++) {
         for (k=i+1;k<=number;k++){
            if (arr[k]%arr[i]==0 && contained_number(arr[k],arr[i])) {
               e.v = i;
               e.w = k;
               insertEdge(g,e);    
            }
         }
      }
      // output the answer for task A
      printf("Partial order:\n");
      for (i=0;i<g->nV-1;i++) {
         printf("%d:",arr[i]);
         for (k=i+1;k<g->nV;k++) {
            if (adjacent(g,i,k)) {
               printf(" %d",arr[k]);   
            }  
         }
         printf("\n");
      }
      printf("%d:\n",arr[i]);

      // -- task B --
      // TIME COMPLEXITY: O(n*n*n), which n is the number of divisors.
      printf("\n");
      printf("Longest monotonically increasing sequences:\n");
      int maxlenth=0;
      for (m=0;m<g->nV;m++) {
         depth_recursive(m,g);
      }
      // compute the longest lenth of route, I also store the maxlenth in dp[999]
      // for use in the print_route function.
      for (m=0;m<g->nV;m++) {
         maxlenth = max(maxlenth,dp[m]);
      }
      dp[999] = maxlenth;
      // print out the route which have the same lenth as maxlenth
      for (m=0;m<g->nV;m++) {
         if (dp[m]==maxlenth) {
            int history[1000];
            print_route(m,g,arr,history);
         }
      }
      // free the memory used by the graph.
      freeGraph(g);
      return 0;
   }
}

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------

// This function is used to judge if number a contains all digits in number b
// e.g: contained_number(19,1) returns 1 since '19' contains all digits in '1'
//      while contained_number(499,1) returns 0 because '499' doesn't contain '1'.
int contained_number(int a, int b) {
   if (a<b) {
      return 0; 
   } else {
      char aa[15];
      char bb[15];
      sprintf(aa,"%d",a);
      sprintf(bb,"%d",b);
      int i=0;
      int k=0;
      int number = 0;
      while (bb[i]!='\0') {
         int flag = 0;
         while (aa[k]!='\0') {
            if (bb[i] == aa[k]) {
               flag = 1;
               k=0;
               break; 
            } else {
               k++; 
            }
         }
         if (flag==0) {
            return 0; 
         }
         i++;    
      }
      return 1;
   }
}

// this function inputs two integers and return the larger one
int max(int A, int B) {
   if (A>B) {
      return A; 
   } else {
      return B; 
   }
}

// this function is used to mark each node with a depth recursively
// e.g. if dp[i] = n, means that from node[i] have at most n steps to go to the end.
int depth_recursive(int i, Graph g) {
   if (dp[i]) {
      return dp[i]; 
   }
   for (int j=i+1;j<g->nV;j++) {
      if (adjacent(g,i,j)) {
         dp[i] = max(dp[i], depth_recursive(j,g)+1);
      }
   }
   return dp[i];
}

// this function is used to print all longest route in ascending order start from a specific node
void print_route(int i, Graph g, int *arr ,int history[]) {
   if (dp[i]==0 && dp[999]!=0) {
      int m;
      printf("%d",history[dp[999]]);
      for (m=dp[999]-1;m>=0;m--) {
         printf(" < %d",history[m]);
      }
      printf("\n");
   }
   history[dp[i]]=arr[i];
   if (dp[999]==0) {
      printf("%d\n",arr[i]);
   }
   for (int j=i;j<g->nV;j++) {
      if (adjacent(g,i,j) && dp[i]==dp[j]+1) {
         history[dp[j]]=arr[j];
         print_route(j, g, arr, history);
      }
   }
}
// Insertion Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "insertionsort.h"
int InsertionSortCompares=0;
int InsertionSortMemaccess=0;
void InsertionSort(std::vector<int>* numbers) {
   int i = 0;
   int j = 0;
   int temp = 0;  // Temporary variable for swap
   
   for (i = 1; i < (int)numbers->size(); ++i) {
      j = i;
      // Insert numbers[i] into sorted part
      // stopping once numbers[i] in correct position
	  InsertionSortCompares+=1;
	  InsertionSortMemaccess+=2;
      while (j > 0 && (*numbers)[j] < (*numbers)[j - 1]) {
         // Swap numbers[j] and numbers[j - 1]
         temp = (*numbers)[j];
		 InsertionSortMemaccess+=1;
         (*numbers)[j] = (*numbers)[j - 1];
		 InsertionSortMemaccess+=2;
         (*numbers)[j - 1] = temp;
		 InsertionSortMemaccess+=1;
         --j;
      }
   }
   
   return;
}
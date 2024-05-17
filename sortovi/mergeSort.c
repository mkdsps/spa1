#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//https://www.youtube.com/watch?v=LeWuki7AQLo

void ispis(int niz[], int n){
   for (int i = 0 ; i < n ; i++)
      printf("%d ", niz[i]);
   printf("\n");

}

void mergeSort(int niz[], int n);
void mergeSortRecusrion(int niz[], int l, int r);
void merge_sorted_arrays(int niz[], int l, int s, int r);


int main(){
   int niz[] = {9, 4, 8, 1, 7, 0, 3, 2, 5 ,6};
   int n = sizeof(niz)/ sizeof(int);
   mergeSort(niz,n);
   ispis(niz,n);
}

void mergeSort(int niz[], int n){
   mergeSortRecusrion(niz, 0, n - 1);
}

void mergeSortRecusrion(int niz[], int l, int r)
{
   if(l<r){
      int m = l + (r-l)/2; 
      mergeSortRecusrion(niz, l, m);
      mergeSortRecusrion(niz, m + 1, r);

      merge_sorted_arrays(niz,l,m,r);
   }
}

void merge_sorted_arrays(int niz[], int l, int m, int r){
   int left_length = m - l + 1;
   int right_length = r - m;

   int *temp_left = (int*)malloc(left_length*sizeof(int));
   int *temp_right = (int*)malloc(right_length*sizeof(int));

   for (int i = 0 ; i < left_length ; i++)
      temp_left[i] = niz[i+l];
   for (int i = 0 ; i < right_length ; i++)
      temp_right[i] = niz[i+m+1];

   for (int i = 0, j = 0, k = l; k <= r; k++){
      if(i < left_length && (j>=right_length || temp_left[i] < temp_right[j]))
         niz[k] = temp_left[i++];
      else
         niz[k] = temp_right[j++];
   }

   free(temp_left);
   free(temp_right);
   
}

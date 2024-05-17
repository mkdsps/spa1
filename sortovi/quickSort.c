#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//https://www.youtube.com/watch?v=0jDiBM68NGU

void ispis(int niz[], int n){
   for (int i = 0 ; i < n ; i++)
      printf("%d ", niz[i]);
   printf("\n");

}

void swap(int* a , int* b){
   int k = *a;
   *a = *b;
   *b = k;
}

void quickSort(int niz[], int n);
void quickSortRecursion(int niz[], int l, int r);
int partition(int niz[],int l, int r);

int main(){
   int niz[] = {9, 4, 8, 1, 7, 0, 3, 2, 5 ,6};
   int n = sizeof(niz)/ sizeof(int);
   quickSort(niz,n);
   ispis(niz,n);
}

void quickSort(int niz[], int n){
   quickSortRecursion(niz, 0, n-1);
}

void quickSortRecursion(int niz[], int l, int r)
{
   if(l<r){
      int mid = partition(niz, l, r);
      quickSortRecursion(niz, l, mid-1);
      quickSortRecursion(niz, mid+1, r);
   }
}

int partition(int niz[],int l, int r){
   int pivot = niz[r];
   int poslednjaPozicijaManjih = l;
   for (int i = l; i < r ; i++){
      if (niz[i] < pivot)
         swap(&niz[i], &niz[poslednjaPozicijaManjih++]);
         
   }
   swap(&niz[poslednjaPozicijaManjih], &niz[r]);
   return poslednjaPozicijaManjih;
}


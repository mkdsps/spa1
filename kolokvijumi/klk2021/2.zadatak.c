#include <stdio.h>
#include <stdlib.h>

typedef struct element{
   float data;
   struct element* sledeci;
} element;

element* alociraj(float data){
   element *res = (element*)malloc(sizeof(element));
   res->sledeci = NULL;
   res->data = data;

   return res;
}

void dodaj(element** glava, element* novi){
   if (*glava != NULL)
      novi->sledeci = *glava;
   *glava = novi;
}

void ispis(element *glava){
   while(glava!= NULL){
      printf("%f ",  glava->data);
      glava = glava->sledeci;
   }
   putchar('\n');
}

void ubaci(element **glava, element* el){
   if(*glava == NULL){
      *glava = el;
      return;
   }

   if((*glava)->data < el->data){
      el->sledeci = *glava;
      *glava = el;
      return;
   }

   element *tr = *glava;
   while(tr->sledeci != NULL){
      if(tr->sledeci->data < el->data){
         el->sledeci = tr->sledeci;
         tr->sledeci = el;
         return;
      }
      tr=tr->sledeci;
   }
   el->sledeci = tr->sledeci;
   tr->sledeci = el;

}


void izbaci(element **glava, element**noviGlava, int k){
   element *pr = NULL;
   element *tr = *glava;

   while(tr != NULL){
      if((int)(tr->data*100) % 100 < k){
         element* izbaceni = tr;
         tr=tr->sledeci;
         izbaceni->sledeci = NULL;
         
         if (pr != NULL)
            pr->sledeci = tr;
         else
            *glava = tr;

         ubaci(noviGlava, izbaceni);

      }
      else{
         pr = tr;
         tr = tr->sledeci;
      }
   }
}

int main(){
   element* glava = NULL;
   int n;
   scanf("%d", &n);
   for (int i = 0 ; i < n ; i++){
      float data;
      scanf("%f", &data);
      element* novi = alociraj(data);
      dodaj(&glava, novi);
   }
   int k;
   scanf("%d", &k);
   ispis(glava);

   element *novi = NULL;
   izbaci(&glava, &novi, k);

   ispis(novi);
   ispis(glava);
}

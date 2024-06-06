#include<stdio.h>
#include<stdlib.h>

typedef struct element{
   int broj;
   struct element *sledeci;
}element;

element* alociraj(int broj){
   element* novi = (element *)malloc(sizeof(element));

   novi->sledeci = NULL;
   novi->broj = broj;
   return novi;
}

void dodaj(element **glava, element* novi){
   if (*glava == NULL){
      *glava = novi;
      return;
   }

   element* tr = *glava;
   while(tr->sledeci != NULL)
      tr = tr->sledeci;
   tr->sledeci = novi;
}

void ispis(element *glava){
   while(glava != NULL){
      printf("%d ", glava->broj);
      glava = glava->sledeci;
   }
   printf("\n");
}

void dodajNaPocetak(element **glava, element* novi){
   if(*glava == NULL){
      *glava = novi;
      return;
   }

   novi->sledeci = *glava;
   *glava = novi;
}

void izbaci(element** glava, element**glavaNovi){
   element *trenutni = *glava;
   while(trenutni != NULL &&  trenutni->sledeci != NULL && trenutni->sledeci->sledeci != NULL){
      element *prvi = trenutni;
      element *drugi = prvi->sledeci;
      element *treci = drugi->sledeci;
      
      if (prvi->broj <= drugi->broj || drugi->broj >= treci->broj){
         drugi->sledeci = NULL;
         prvi->sledeci = treci;
         dodajNaPocetak(glavaNovi, drugi);
      }
      trenutni = treci->sledeci;
   }
}


int main(){
   element* glava = NULL;
   int n;
   scanf("%d", &n);

   for (int i = 0 ; i < n ; i++){
      int broj;
      scanf("%d", &broj);
      element* novi = alociraj(broj);
      dodaj(&glava, novi);
   }

   ispis(glava);
   element *noviGlava = NULL;
   izbaci(&glava, &noviGlava);
   ispis(glava);
   ispis(noviGlava);

}

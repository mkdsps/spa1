#include <stdio.h>
#include <stdlib.h>

typedef struct element {
   int data;
   struct element* sledeci;
} element;

element* alociraj(int data) {
   element* el = (element *)malloc(sizeof(element));
   if (el == NULL) {
       printf("Memory allocation failed\n");
       exit(1);
   }
   el->data = data;
   el->sledeci = NULL;
   return el;
}

void dodajNaKraj(element** glava, element *el) {
    if (*glava == NULL) { 
        *glava = el;
        return;
    }

    element *pok = *glava;
    while (pok->sledeci != NULL)
        pok = pok->sledeci;
    pok->sledeci = el;
}

void ispis(element* glava) {
   while (glava != NULL) {
      printf("%d ", glava->data);
      glava = glava->sledeci;
   }
   printf("\n");
}

void dodajNaPocetak(element **glava, element *el){
   if(*glava == NULL){
      *glava = el;
      return;
   }
   el->sledeci = *glava;
   *glava = el;
}

void razvrstaj(element* glava, element** prva, element** druga) {
   element* trenutni = glava;
   element* sledeci;
   int k = 1;
   while (trenutni != NULL) {
      sledeci = trenutni->sledeci;

      trenutni->sledeci = NULL;

      if (k%2) 
         dodajNaKraj(prva, trenutni);
      else 
         dodajNaKraj(druga, trenutni);
      
      trenutni = sledeci;
      k++;
   }
}

int main() {
   element* glava = NULL;
   element* prva = NULL;
   element* druga = NULL;

   int n;
   scanf("%d", &n);
   for (int i = 0; i < n; i++) {
      int x;
      scanf("%d", &x);
      element* novi = alociraj(x);
      dodajNaPocetak(&glava, novi);
   }

   ispis(glava); 
   razvrstaj(glava, &prva, &druga);

   ispis(prva);
   ispis(druga);
   return 0;
}

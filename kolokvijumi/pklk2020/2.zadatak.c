#include <stdio.h>
#include <stdlib.h>

typedef struct element{
   char slovo;
   struct element* sledeci;
} element;

element *alociraj(char c){
   element* novi = (element *)malloc(sizeof(element));
   novi->sledeci = NULL;
   novi->slovo = c;

   return novi;
}

void dodajNaPocetak(element **glava, element* el){
   el->sledeci = *glava;
   *glava = el;
}

void ispisi(element *glava){
   while(glava!= NULL){
      putchar(glava->slovo);
      glava = glava->sledeci;
   }
   putchar('\n');
}

void dodajNaKraj(element**glava, element* el){
   if(*glava == NULL) {*glava = el; return;}
   
   element *tren = *glava;
   while(tren->sledeci != NULL)
      tren = tren->sledeci;
   tren->sledeci = el;
}

void razvrstaj(element **glava, element **novaGlava){
   element* pre = NULL;
   element* tren = *glava;

   while(tren && tren->sledeci && tren->sledeci->sledeci){
      element*prvi = tren;
      element*zadnji = tren->sledeci->sledeci;
      if(prvi->slovo == zadnji->slovo){
         
         if(pre == NULL){
            *glava = zadnji->sledeci;
         }
         else{
            pre->sledeci = zadnji->sledeci;
         }
         tren = zadnji->sledeci;
         zadnji->sledeci = NULL;
         dodajNaKraj(novaGlava, prvi);
      }
      else{
         pre = tren->sledeci->sledeci;
         tren = pre->sledeci;
      }
   }
}

int main(){
   element *glava = NULL;
   int n;
   scanf("%d", &n);
   getchar();
   for (int i = 0 ; i < n ; i++){
      char c;
      scanf("%c", &c);
      element*novi = alociraj(c);
      dodajNaPocetak(&glava, novi);
   }

   ispisi(glava);
   element* novaGlava = NULL;
   razvrstaj(&glava, &novaGlava);

   ispisi(glava);
   ispisi(novaGlava);
}

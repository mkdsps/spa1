#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element
{
   char data;
   struct element* sledeci;
}element;

element* alociraj(char c){
   element *novi = (element*)malloc(sizeof(element));
   novi->data = c;
   novi->sledeci = NULL;
   return novi;
}

void ispisi(element* glava){
   while(glava){
      printf("%c ", glava->data);
      glava = glava->sledeci;
   }
   printf("\n");
}

void dodajNaKraj(char c, element **glava){
   if(*glava == NULL){
      *glava = alociraj(c);
      return;
   }

   element *pok = *glava;
   while(pok->sledeci != NULL)
      pok = pok->sledeci;

   pok->sledeci = alociraj(c);
}

void dodajNaPocetak(element* novi, element**glava){
   novi->sledeci = *glava;
   *glava = novi;
}

void razvrstaj(element* glava, element**samoglasnici, element**suglasnici){
   while(glava){
      element *tren = glava;
      glava = glava->sledeci;
      if(tren->data == 'a' || tren->data == 'e' || tren->data == 'i' || tren->data == 'o' || tren->data == 'u'){
         dodajNaPocetak(tren, samoglasnici);
      }else{
         dodajNaPocetak(tren, suglasnici);
      }

   }
}

int main(){
   element* glava = NULL;
   int n;
   scanf("%d", &n);
   getchar();
   char c;

   for (int i = 0 ; i < n ; i++){
      scanf("%c", &c);
      getchar();
      dodajNaKraj(c, &glava);
   }
   ispisi(glava);

   element* sam = NULL;
   element* sug = NULL;
   razvrstaj(glava, &sam, &sug);

   printf("lista samoglasnika: ");
   ispisi(sam);
   printf("lista suglasnika: ");
   ispisi(sug);
}




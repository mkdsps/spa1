#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct klub
{
   char *naziv;
   char *grad;
   int bodovi, golovi;
}klub;

typedef struct utakmica
{
   char *naziv_domacina;
   char *naziv_gostujuceg;
   int golovi_domaceg, golovi_gostujuceg;
}utakmica;

klub* ucitajKlubove(int *n){
   FILE *fajl = fopen("klubovi.txt", "r");
   fscanf(fajl, "%d", n);
   fgetc(fajl);
   
   klub* k = (klub *)malloc(*n * sizeof(klub));
   char *linija = (char *)malloc(255*sizeof(char));

   for (int i = 0 ; i < *n ; i++){
      fgets(linija, 255, fajl);
      linija[strlen(linija)-1] = '\0';
      k[i].naziv = (char *)malloc((1+strlen(linija)) * sizeof(char));
      strcpy(k[i].naziv, linija);

      fgets(linija, 255, fajl);
      linija[strlen(linija)-1] = '\0';
      k[i].grad = (char *)malloc((1+strlen(linija)) * sizeof(char));
      strcpy(k[i].grad, linija);

      fscanf(fajl, "%d", &k[i].bodovi);
      fgetc(fajl);

      fscanf(fajl, "%d", &k[i].golovi);
      fgetc(fajl);
   }

   free(linija);
   fclose(fajl);
   return k;
}

utakmica* ucitajUtakmice(int n){
   FILE * fajl = fopen("poslednje_kolo.txt","r");
   utakmica* u = (utakmica*)malloc(n * sizeof(utakmica));
   char *linija = (char *)malloc(255 * sizeof(char));


   for (int i = 0 ; i < n/2 ; i++){
      fgets(linija, 255, fajl);
      linija[strlen(linija)-1] = '\0';
      u[i].naziv_domacina = (char *)malloc((1+strlen(linija)) * sizeof(char));
      strcpy(u[i].naziv_domacina, linija);

      fgets(linija, 255, fajl);
      linija[strlen(linija)-1] = '\0';
      u[i].naziv_gostujuceg = (char *)malloc((1 + strlen(linija))*sizeof(char));
      strcpy(u[i].naziv_gostujuceg, linija);

      fscanf(fajl, "%d", &u[i].golovi_domaceg);
      fgetc(fajl);

      fscanf(fajl, "%d", &u[i].golovi_gostujuceg);
      fgetc(fajl);
   }
   free(linija);
   fclose(fajl);
   return u;
}

void azuriraj(klub* k, char *naziv, int golovi, int bodovi){
   for (int i = 0 ; 1 ; i++)
      if(strcmp(k[i].naziv,naziv) == 0){
         k[i].golovi += golovi;
         k[i].bodovi += bodovi;
         return;
      }
}

void azurirajSve(int n, klub* k, utakmica* u){
   for (int i = 0 ; i < n/2 ; i++){
      if(u[i].golovi_domaceg > u[i].golovi_gostujuceg){
         azuriraj(k, u[i].naziv_domacina, u[i].golovi_domaceg, 3);
         azuriraj(k, u[i].naziv_gostujuceg, u[i].golovi_gostujuceg, 0);
      }
      else if(u[i].golovi_domaceg < u[i].golovi_gostujuceg){
         azuriraj(k, u[i].naziv_domacina, u[i].golovi_domaceg, 0);
         azuriraj(k, u[i].naziv_gostujuceg, u[i].golovi_gostujuceg, 3);
      }
      else{
         azuriraj(k, u[i].naziv_domacina, u[i].golovi_domaceg, 1);
         azuriraj(k, u[i].naziv_gostujuceg, u[i].golovi_gostujuceg, 1);
      }
   }
}

int proveri(klub a, klub b){
   if(a.bodovi > b.bodovi || (a.bodovi == b.bodovi && a.golovi > b.golovi)) return 1;
   return 0;
}

void swap(klub *a, klub *b){
   klub c = *a;
   *a = *b;
   *b = c;
}

void quickSort(klub* a, int n);
void recursion(klub*a, int l, int d);
int partition(klub*a, int l, int d);

int main(){
   int n;
   klub* klubovi = ucitajKlubove(&n);
   utakmica* utakmice = ucitajUtakmice(n);
   azurirajSve(n, klubovi, utakmice);
   quickSort(klubovi, n);
   printf("%s - %s - %d - %d", klubovi[0].naziv, klubovi[0].grad, klubovi[0].bodovi, klubovi[0].golovi);
}

void quickSort(klub* a, int n){
   recursion(a, 0, n-1);
}

void recursion(klub*a, int l, int d){
   if (l < d){
      int s = partition(a, l, d);
      recursion(a, l , s - 1);
      recursion(a, s + 1 , d);
   }
}

int partition(klub*a, int l, int d){
   int brojac = l;
   
   for (int i = l ; i < d ; i++){
      if (proveri(a[i], a[d]))
         swap(&a[i], &a[brojac++]);
   }
   swap(&a[d], &a[brojac]);
   return brojac;
}

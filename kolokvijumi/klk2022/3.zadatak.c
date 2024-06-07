#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINIJA 256

typedef struct {
  char *naziv;
  char grupa;
  int bodovi;
  int golovi;
} reprezentacija;

typedef struct {
  char *domaci;
  char *gostujuci;
  int domaciGolovi;
  int gostujuciGolovi;
} utakmica;

reprezentacija* ucitajReprezentacije(int *n){
   FILE *file = fopen("reprezentacije.txt", "r");
   fscanf(file, "%d", n);
   fgetc(file);

   reprezentacija* reprezentacije = (reprezentacija *)malloc(*n * sizeof(reprezentacija));
   char *linija = (char *)malloc(LINIJA * sizeof(char));

   for (int i = 0 ; i < *n ; i++){
      fgets(linija,LINIJA, file);
      linija[strlen(linija)-1] = '\0';
      reprezentacije[i].naziv = (char *)malloc(strlen(linija) * sizeof(char));
      strcpy(reprezentacije[i].naziv, linija);

      reprezentacije[i].grupa = fgetc(file);
      fgetc(file);

      reprezentacije[i].bodovi = 0;
      reprezentacije[i].golovi = 0;
   }

   free(linija);
   fclose(file);
   return reprezentacije;
}

utakmica* ucitajUtakmice(int *n){
   FILE *file = fopen("utakmice.txt","r");
   fscanf(file, "%d", n);
   fgetc(file);
   utakmica* utakmice = (utakmica *)malloc(*n * sizeof(utakmica));
   char *linija = (char *)malloc(LINIJA * sizeof(char));

   for (int i = 0 ; i < *n ; i++){
      fgets(linija, LINIJA, file);
      linija[strlen(linija)-1] = '\0';
      utakmice[i].domaci = (char*)malloc((1+ strlen(linija)) * sizeof(char));
      strcpy(utakmice[i].domaci, linija);
      
      int k;
      fscanf(file, "%d", &k);
      fgetc(file);
      utakmice[i].domaciGolovi = k;

      fgets(linija, LINIJA, file);
      linija[strlen(linija)-1] = '\0';
      utakmice[i].gostujuci = (char *)malloc((1 + strlen(linija))*sizeof(char));
      strcpy(utakmice[i].gostujuci, linija);

      fscanf(file, "%d", &k);
      fgetc(file);
      utakmice[i].gostujuciGolovi = k;
      //printf("%s %d %s %d \n", utakmice[i].domaci, utakmice[i].domaciGolovi , utakmice[i].gostujuci,  utakmice[i].gostujuciGolovi);
   }

   free(linija);
   fclose(file);
   return utakmice;
}

void azuriraj(reprezentacija* reprezentacije, int n, char* naziv, int golovi, int bodovi){
   for (int i = 0 ; i < n ; i++)
      if (strcmp(naziv, reprezentacije[i].naziv) == 0){
         reprezentacije[i].golovi += golovi;
         reprezentacije[i].bodovi += bodovi;
      }
   
}

void odrediBodove(reprezentacija* reprezentacije, int n, utakmica* utakmice, int m){
   for (int i = 0 ; i < m ; i++){
      char grupaDomacih, grupaGostujucih;
      for (int j = 0 ; j < n ; j++){
         if (strcmp(utakmice[i].domaci,reprezentacije[j].naziv) == 0)
            grupaDomacih = reprezentacije[j].grupa;
         else if(strcmp(utakmice[i].gostujuci, reprezentacije[j].naziv) == 0)
            grupaGostujucih = reprezentacije[j].grupa;
      }

      if(grupaDomacih == grupaGostujucih){
         if(utakmice[i].domaciGolovi > utakmice[i].gostujuciGolovi){
            azuriraj(reprezentacije, n, utakmice[i].domaci, utakmice[i].domaciGolovi, 3);
            azuriraj(reprezentacije, n, utakmice[i].gostujuci, utakmice[i].gostujuciGolovi, 0);
         }
         else if(utakmice[i].domaciGolovi < utakmice[i].gostujuciGolovi){
            azuriraj(reprezentacije, n, utakmice[i].domaci, utakmice[i].domaciGolovi, 0);
            azuriraj(reprezentacije, n, utakmice[i].gostujuci, utakmice[i].gostujuciGolovi, 3);
         }else{
            azuriraj(reprezentacije, n, utakmice[i].domaci, utakmice[i].domaciGolovi, 1);
            azuriraj(reprezentacije, n, utakmice[i].gostujuci, utakmice[i].gostujuciGolovi, 1);
         }
      }

   }
}

void ispisiPobednikeGrupa(reprezentacija* reprezentacije, int n) {
    int m = 0;
    reprezentacija* pobednici = (reprezentacija*)malloc(n * sizeof(reprezentacija));
    int* niz = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        if (niz[i] == 0) {
            pobednici[m] = reprezentacije[i];
            for (int j = i + 1; j < n; j++) {
                if (niz[j] == 0 && pobednici[m].grupa == reprezentacije[j].grupa) {
                    niz[j] = 1;
                    if (pobednici[m].bodovi < reprezentacije[j].bodovi ||
                        (pobednici[m].bodovi == reprezentacije[j].bodovi && pobednici[m].golovi < reprezentacije[j].golovi)) {
                        pobednici[m] = reprezentacije[j];
                    }
                }
            }
            printf("%s %c %d %d\n", pobednici[m].naziv, pobednici[m].grupa, pobednici[m].bodovi, pobednici[m].golovi);
            m++;
        }
    }

    free(pobednici);
    free(niz);
}

void pronadjiNajviseGolova(reprezentacija* rep, int n){
   reprezentacija najviseGolova = rep[0];
   for (int i = 1 ; i < n ; i++)
      if(rep[i].golovi > najviseGolova.golovi)
         najviseGolova = rep[i];
   printf("%s %d", najviseGolova.naziv, najviseGolova.golovi);
}

int main(){
   int n, m;
   reprezentacija* rep = ucitajReprezentacije(&n);
   utakmica* utakmice = ucitajUtakmice(&m);

   odrediBodove(rep, n, utakmice, m);
   ispisiPobednikeGrupa(rep, n);
   pronadjiNajviseGolova(rep, n);
}

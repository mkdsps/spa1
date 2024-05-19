#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct klub
{
   char naziv[100];
   char grad[100];
   int brojBodova, brojGolova
} klub;

typedef struct rezultat
{
   char naziv_domaceg[100];
   char naziv_gostujuceg[100];
   int domaciGolovi, gostujuciGolovi;

} rezultat;

void ucitajKlubove(klub res[], int* n){
   FILE * file = fopen("klubovi.txt","r");
   fscanf(file, "%d", n);
   fgetc(file);

   for (int i = 0 ; i < *n ; i++){
      fgets(res[i].naziv, 100, file);
      res[i].naziv[strcspn(res[i].naziv, "\n")] = '\0';
      
      fgets(res[i].grad, 100, file);
      res[i].grad[strcspn(res[i].grad, "\n")] = '\0';

      fscanf(file, "%d %d", &res[i].brojBodova, &res[i].brojGolova);
      fgetc(file);
   }

}

void ucitajRezultate(rezultat res[], int n){
   FILE *file = fopen("poslednje_kolo.txt", "r");
   
   for (int i = 0 ; i < n ; i++){
      fgets(res[i].naziv_domaceg, 100, file);
      res[i].naziv_domaceg[strcspn(res[i].naziv_domaceg, "\n")] = '\0';
      fgets(res[i].naziv_gostujuceg, 100, file);
      res[i].naziv_gostujuceg[strcspn(res[i].naziv_gostujuceg, "\n")] = '\0';

      fscanf(file, "%d %d", &res[i].domaciGolovi, &res[i].gostujuciGolovi);
      fgetc(file);

   }
}

void azuriraj(klub klubovi[], rezultat rezultati[], int n) {
    for (int i = 0; i < n; i++) {
        int pobednik = 0;
        if (rezultati[i].domaciGolovi > rezultati[i].gostujuciGolovi)
            pobednik = 1;
        else if (rezultati[i].domaciGolovi < rezultati[i].gostujuciGolovi)
            pobednik = 2;

        for (int j = 0; j < n; j++) {
            if (strcmp(klubovi[j].naziv, rezultati[i].naziv_domaceg) == 0) {
                klubovi[j].brojGolova += rezultati[i].domaciGolovi;
                if (pobednik == 1) {
                    klubovi[j].brojBodova += 3;
                } else if (pobednik == 0) {
                    klubovi[j].brojBodova += 1;
                }
            } else if (strcmp(klubovi[j].naziv, rezultati[i].naziv_gostujuceg) == 0) {
                klubovi[j].brojGolova += rezultati[i].gostujuciGolovi;
                if (pobednik == 2) {
                    klubovi[j].brojBodova += 3;
                } else if (pobednik == 0) {
                    klubovi[j].brojBodova += 1;
                }
            }
        }
    }
}
int uporediKlubove(klub a, klub b){
   //funkcija vraca jedan ako je klub b bolji od kluba a;
   if(a.brojBodova > b.brojBodova || (a.brojBodova == b.brojBodova && a.brojGolova > b.brojGolova)) 
      return 1;
   return 0;
}
void spoji(klub klubovi[], int l, int s, int d){
   int leva_duzina = s - l + 1;
   int desna_duzina = d-s;

   klub *temp_levo = (klub*)malloc(leva_duzina * sizeof(klub));
   klub *temp_desno = (klub*)malloc(desna_duzina* sizeof(klub));

   for (int i = 0 ; i < leva_duzina ; i++)
      temp_levo[i] = klubovi[i+l];
   for (int i = 0 ; i < desna_duzina ; i++)
      temp_desno[i] = klubovi[i+s+1];

   int i = 0, j = 0;
   for (int k = l; k <= d; k++){
      if (j >= desna_duzina || (i < leva_duzina && uporediKlubove(temp_levo[i], temp_desno[j])))
         klubovi[k] = temp_levo[i++];
      else
         klubovi[k] = temp_desno[j++];
   }
   free(temp_desno);
   free(temp_levo);
}

void mergeSort(klub klubovi[], int l, int d){
   if(l < d){
      int s = l + (d-l)/2;
      mergeSort(klubovi, l, s);
      mergeSort(klubovi, s + 1 , d);

      spoji(klubovi, l, s, d);
   }
}

void sortiraj(klub klubovi[], int n){
   mergeSort(klubovi, 0, n-1);
}

int main(){
   int n;
   klub klubovi[100];
   rezultat rezultati[100];
   ucitajKlubove(klubovi, &n);
   ucitajRezultate(rezultati, n);
   azuriraj(klubovi,rezultati, n);
   sortiraj(klubovi, n);
   printf("%s - %s - %d poena - %d golova", klubovi[0].naziv, klubovi[0].grad, klubovi[0].brojBodova, klubovi[0].brojGolova);
}

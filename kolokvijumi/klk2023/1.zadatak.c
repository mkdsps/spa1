#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int binnari(char* niz, int k, int duzina){
   if(niz[k] !=  '0' && niz[k] != '1') return 0;
   int tren = niz[k]- '0';
   return pow(2, duzina-k-1) * tren + binnari(niz, k+1, duzina); 
}

int uBinarni(char *niz, int duzina){
   return binnari(niz, 0, duzina);
}



int main(){
   char* input = (char *)malloc(sizeof(char));

   fgets(input, 1000, stdin);
   

   for (int i = 0 ; input[i] != '\0' ; i++){
      if(input[i] == '0' || input[i] =='1'){
         int j = i;
         while(input[j] == '1' || input[j] =='0')
            j++;

         int len = j - i;
         char* bin = (char*)malloc(1000*sizeof(char));
         for (int k = 0 ; k < len ; k++)
            bin[k] = input[i+k];
         bin[len] = '\0';
         printf("%d",uBinarni(bin, len));
         free(bin);
         i=j;
      }
      else
         putchar(input[i]);
   }
   free(input);

}




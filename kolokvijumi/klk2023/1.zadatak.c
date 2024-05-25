#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int binnari(char* niz, int k, int duzina){
   if (duzina <= k) return 0;
   int tren = niz[k]-'0';
   return pow(2, duzina-k-1)*tren + binnari(niz, k+1, duzina);
}

int uBinarni(char *niz, int duzina){
   
   return binnari(niz, 0, duzina);
}

int main(){
   
   char c;
   c = getchar();
   while (c != '\n' && c != EOF){
      if(c == '0' || c =='1'){
         int i = 0, n = 1000;
         char* bin = (char*)malloc(n*sizeof(char));
         while(c == '1' || c =='0'){
            if (i >= n){
               n+= 1000;
               bin = (char *)realloc(bin, n * sizeof(char));
            }

            bin[i++] = c;
            c = getchar();
            
         }
         printf("%d",uBinarni(bin, i));
         free(bin);
      }
      else{
         putchar(c);
         c = getchar();
      }
   }


}

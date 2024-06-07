#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LINE 255

int rek(char* broj, int n){
   if(n == 0) return 0;
   return (broj[0]-'0')*pow(2, n-1) + rek(broj+1, n-1);
}

int main(){
   char c = getchar();
   
   while(c != '\n'){
      if(c == '0' || c == '1'){
         int duzina = LINE;
         char *broj = (char *)malloc(duzina* sizeof(char));
         int k = 0;
         while(c == '0' || c == '1'){
            if(k > duzina){
               duzina+=LINE;
               broj = (char*)realloc(broj, duzina*sizeof(char));
            }
            broj[k++] = c;
            c = getchar();
         }
         broj[k] = '\0';
         printf("%d", rek(broj, k));
         free(broj);
      }
      else{
         putchar(c);
         c = getchar();
      }
   }
}
